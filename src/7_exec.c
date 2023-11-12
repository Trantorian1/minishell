/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:04:00 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 13:54:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "s_cmd.h"
#include "d_str.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

#define F_IN O_RDONLY | O_CREAT
#define F_OUT O_WRONLY | O_CREAT
#define F_APPEND O_WRONLY | O_APPEND | O_CREAT

static void	check_for_builtin(
	t_data *_Nonnull data
);
static void	fork_commands(
	t_data *_Nonnull data
);
static uint8_t	child(
	t_data *_Nonnull data,
	size_t index,
	int32_t read_fd,
	int32_t pipe_id[2]
);

uint8_t	state_exec(t_data *_Nonnull data)
{
	if (data == NULL || data->cmd->len < 1)
		return (EXIT_FAILURE);

	if (data->cmd->len == 1)
		check_for_builtin(data);
	else
		fork_commands(data);

	return (EXIT_SUCCESS);
}

static void	check_for_builtin(t_data *_Nonnull data)
{
	t_cmd		cmd;
	t_builtin	builtin;

	cmd = vptr_get(t_cmd, data->cmd, 0);
	builtin = builtin_get(cmd.arg[0]);

	if (builtin != BUILTIN_NONE)
		safe_exec(data, cmd);
	else
		fork_commands(data);
}

static void	fork_commands(t_data *_Nonnull data)
{
	size_t	index;
	int32_t	read_fd;
	int32_t	pipe_id[2];

	index = 0;
	read_fd = STDIN_FILENO;

	while (index < data->cmd->len)
	{
		safe_pipe(pipe_id);

		if (safe_fork() == 0)
			child(data, index, read_fd, pipe_id);
		else
		{
			if (index != 0)
				safe_close(read_fd);

			safe_close(pipe_id[PIPE_WRITE]);
			read_fd = pipe_id[PIPE_READ];
		}

		index++;
	}
	safe_close(read_fd);

	while (wait(NULL) != -1 && errno != ECHILD)
		continue ;
}

static uint8_t	redir_heredoc(t_str content)
{
	int32_t	pipe_id[2];

	safe_pipe(pipe_id);

	if (write(pipe_id[PIPE_WRITE], content.get, content.len) == -1)
	{
		perror("could not write to heredoc");
		return (EXIT_FAILURE);
	}

	safe_dup2(pipe_id[PIPE_READ], STDIN_FILENO);
	safe_close(pipe_id[PIPE_READ]);
	safe_close(pipe_id[PIPE_WRITE]);

	return (EXIT_SUCCESS);
}

static uint8_t	redir_file(t_str file, int32_t flags, int32_t stream)
{
	int32_t	fd;

	if (stream < 0)
		return (EXIT_FAILURE);

	fd = open(file.get, flags, S_IRUSR | S_IWUSR);
	if (fd == - 1)
	{
		perror("could not open file");
		return (EXIT_FAILURE);
	}

	safe_dup2(fd, stream);
	safe_close(fd);

	return (EXIT_SUCCESS);
}

static uint8_t	redir(t_cmd cmd)
{
	size_t	index;
	t_str	*redir;
	t_str	content;
	
	index = 0;
	while (index < cmd.redir->len)
	{
		redir = vptr_get_ptr(t_str, cmd.redir, index);
		content = *(redir + 1);

		if (str_eq(*redir, REDIR_HEREDOC) && redir_heredoc(content))
			return (EXIT_FAILURE);
		else if (str_eq(*redir, REDIR_IN))
		{
			if (redir_file(content, F_IN, STDIN_FILENO))
				return (EXIT_FAILURE);
		}
		else if (str_eq(*redir, REDIR_APPEND))
		{
			if (redir_file(content, F_APPEND, STDOUT_FILENO))
				return (EXIT_FAILURE);
		}
		else if (str_eq(*redir, REDIR_OUT))
		{
			if (redir_file(content, F_OUT, STDOUT_FILENO))
				return (EXIT_FAILURE);
		}

		index += 2;
	}

	return (EXIT_SUCCESS);
}

static uint8_t	child(
	t_data *_Nonnull data,
	size_t index,
	int32_t read_fd,
	int32_t pipe_id[2]
) {
	t_cmd	cmd;

	if (data == NULL)
		return (EXIT_FAILURE);

	cmd = vptr_get(t_cmd, data->cmd, index);

	if (index != 0)
	{
		safe_dup2(read_fd, STDIN_FILENO);
		safe_close(read_fd);
	}

	if (index < data->cmd->len - 1)
		safe_dup2(pipe_id[PIPE_WRITE], STDOUT_FILENO);

	safe_close(pipe_id[PIPE_READ]);
	safe_close(pipe_id[PIPE_WRITE]);

	if (redir(cmd) == EXIT_FAILURE)
		safe_exit(EXIT_FAILURE);

	if (safe_exec(data, cmd) == EXIT_SUCCESS)
		safe_exit(EXIT_SUCCESS);

	safe_free_all();
	safe_exit(EXIT_FAILURE);
}
