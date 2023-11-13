/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:04:00 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 22:02:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_get.h"
#include "e_builtin.h"
#include "safe_exit.h"
#include "state_exec.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "dynamic/alloc.h"

#include "safe_fork.h"
#include "safe_pipe.h"
#include "safe_dup2.h"
#include "safe_close.h"
#include "safe_exec.h"
#include "wait_child.h"

#include "s_cmd.h"
#include "d_str.h"
#include "d_pipe.h"

#define F_IN O_RDONLY
#define F_OUT O_WRONLY | O_CREAT | O_TRUNC
#define F_APPEND O_WRONLY | O_APPEND | O_CREAT

static uint8_t	check_for_builtin(t_data *_Nonnull data);
static uint8_t	fork_commands(t_data *_Nonnull data);
static uint8_t	redir(t_cmd cmd, int32_t pipes[2]);
static uint8_t	child(t_data *_Nonnull data, size_t index, int32_t redirs[2]);

uint8_t	state_exec(t_data *_Nonnull data)
{
	if (data == NULL || data->cmd->len < 1)
		return (EXIT_FAILURE);

	if (data->cmd->len == 1)
		data->exit_code = check_for_builtin(data);
	else
		data->exit_code = fork_commands(data);

	return (EXIT_SUCCESS);
}

static uint8_t	check_for_builtin(t_data *_Nonnull data)
{
	t_cmd		cmd;
	t_builtin	builtin_type;
	int32_t		redirs[2];

	cmd = vptr_get(t_cmd, data->cmd, 0);
	builtin_type = builtin_get(cmd.arg[0]);

	if (builtin_type != BUILTIN_NONE)
	{
		redirs[0] = STDIN_FILENO;
		redirs[1] = STDOUT_FILENO;
		if (redir(cmd, redirs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (builtin(data, cmd, builtin_type, redirs));
	}
	else
		return (fork_commands(data));
}

static uint8_t	fork_commands(t_data *_Nonnull data)
{
	size_t	index;
	int32_t	read_fd;
	int32_t	pipe_id[2] = {STDIN_FILENO , STDOUT_FILENO};
	int32_t	pid;

	index = 0;
	read_fd = STDIN_FILENO;
	pid = 0;

	while (index < data->cmd->len)
	{

		if (index != data->cmd->len - 1)
			safe_pipe(pipe_id);
		else
			pipe_id[PIPE_WRITE] = STDOUT_FILENO;

		pid = safe_fork();

		// child
		if (pid == 0)
		{
			if (index != data->cmd->len - 1)
				safe_close(pipe_id[PIPE_READ]);
			child(data, index, (int32_t []){read_fd, pipe_id[PIPE_WRITE]});
		}

		// parent
		else
		{
			if (index != 0)
				safe_close(read_fd);
			if (index != data->cmd->len - 1)
				safe_close(pipe_id[PIPE_WRITE]);
			read_fd = pipe_id[PIPE_READ];
		}

		index++;
	}

	return (wait_child(pid));
}

static uint8_t	redir_heredoc(
	t_str content,
	int32_t pipes[2]
) {
	int32_t	pipe_id[2];

	safe_pipe(pipe_id);
	safe_close(pipes[PIPE_READ]);

	if (write(pipe_id[PIPE_WRITE], content.get, content.len) < 0)
	{
		perror("could not write to heredoc");
		safe_close(pipe_id[PIPE_WRITE]);
		return (EXIT_FAILURE);
	}

	pipes[PIPE_READ] = pipe_id[PIPE_READ];
	safe_close(pipe_id[PIPE_WRITE]);

	return (EXIT_SUCCESS);
}

static uint8_t	redir_file(
	t_str file, 
	int32_t flags, 
	int32_t	pipes[2]
) {
	int32_t	fd;

	fd = open(file.get, flags, S_IWUSR | S_IRUSR);
	if (flags == (F_IN))
	{
		safe_close(pipes[PIPE_READ]);
		pipes[PIPE_READ] = fd;
	}
	else
	{
		safe_close(pipes[PIPE_WRITE]);
		pipes[PIPE_WRITE] = fd;
	}
	if (fd < 0)
	{
		perror(file.get);
		if (flags == (F_IN))
			safe_close(pipes[PIPE_WRITE]);
		else
			safe_close(pipes[PIPE_READ]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static uint8_t	redir(t_cmd cmd, int32_t pipes[2])
{
	size_t	index;
	t_str	*redir;
	t_str	content;
	
	index = 0;
	while (index < cmd.redir->len)
	{
		printf("index:%zu\n", index);
		redir = vptr_get_ptr(t_str, cmd.redir, index);
		content = *(redir + 1);

		if (str_eq(*redir, REDIR_HEREDOC) && redir_heredoc(content, pipes))
			return (EXIT_FAILURE);
		else if (str_eq(*redir, REDIR_IN))
		{
			if (redir_file(content, F_IN, pipes))
				return (EXIT_FAILURE);
		}
		else if (str_eq(*redir, REDIR_APPEND))
		{
			if (redir_file(content, F_APPEND, pipes))
				return (EXIT_FAILURE);
		}
		else if (str_eq(*redir, REDIR_OUT))
		{
			if (redir_file(content, F_OUT, pipes))
				return (EXIT_FAILURE);
		}

		index += 2;
	}

	return (EXIT_SUCCESS);
}

static uint8_t	child(t_data *_Nonnull data, size_t index, int32_t redirs[2])
{
	t_cmd	cmd;

	if (data == NULL)
		return (EXIT_FAILURE);

	cmd = vptr_get(t_cmd, data->cmd, index);

	if (redir(cmd, redirs) == EXIT_FAILURE)
		safe_exit(EXIT_FAILURE);

	if (redirs[PIPE_READ] != STDIN_FILENO)
	{
		safe_dup2(redirs[PIPE_READ], STDIN_FILENO);
		safe_close(redirs[PIPE_READ]);
	}

	if (redirs[PIPE_WRITE] != STDOUT_FILENO)
	{
		safe_dup2(redirs[PIPE_WRITE], STDOUT_FILENO);
		safe_close(redirs[PIPE_WRITE]);
	}

	// exectute command
	safe_exit(safe_exec(data, cmd, redirs));
}
