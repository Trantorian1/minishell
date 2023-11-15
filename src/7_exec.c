/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:04:00 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 21:23:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "builtin_get.h"
#include "e_builtin.h"
#include "redir.h"
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

static uint8_t	check_for_builtin(t_data *_Nonnull data);
static uint8_t	fork_commands(t_data *_Nonnull data);
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

	cmd = *(t_cmd *)vptr_get(data->cmd, 0);
	if (cmd.arg == NULL)
		builtin_type = BUILTIN_NONE;
	else
		builtin_type = builtin_get(cmd.arg[0]);
	if (builtin_type != BUILTIN_NONE)
	{
		redirs[0] = STDIN_FILENO;
		redirs[1] = STDOUT_FILENO;
		if (redir(cmd, redirs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (builtin(data, cmd, redirs, false));
	}
	else
		return (fork_commands(data));
}

static int32_t	fork_loop(
	size_t *_Nonnull index,
	int32_t *_Nonnull pipe_id,
	t_data *_Nonnull data,
	int32_t *_Nonnull read_fd
) {
	int32_t	pid;

	if (index == NULL || pipe_id == NULL || data == NULL || read_fd == NULL)
		return (EXIT_FAILURE);
	if (*index != data->cmd->len - 1)
		safe_pipe(pipe_id);
	else
		pipe_id[PIPE_WRITE] = STDOUT_FILENO;
	pid = safe_fork();
	if (pid == 0)
	{
		if (*index != data->cmd->len - 1)
			safe_close(pipe_id[PIPE_READ]);
		child(data, *index, (int32_t []){(*read_fd), pipe_id[PIPE_WRITE]});
	}
	else
	{
		if (*index != 0)
			safe_close(*read_fd);
		if (*index != data->cmd->len - 1)
			safe_close(pipe_id[PIPE_WRITE]);
		*read_fd = pipe_id[PIPE_READ];
	}
	(*index)++;
	return (pid);
}

static uint8_t	fork_commands(t_data *_Nonnull data)
{
	size_t	index;
	int32_t	read_fd;
	int32_t	pid;
	int32_t	pipe_id[2];

	index = 0;
	read_fd = STDIN_FILENO;
	pipe_id[0] = STDIN_FILENO;
	pipe_id[1] = STDOUT_FILENO;
	pid = 0;
	while (index < data->cmd->len)
	{
		pid = fork_loop(&index, pipe_id, data, &read_fd);
		if (pid == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (wait_child(pid));
}

static uint8_t	child(t_data *_Nonnull data, size_t index, int32_t redirs[2])
{
	t_cmd		cmd;
	t_builtin	builtin_type;

	if (data == NULL)
		return (EXIT_FAILURE);
	cmd = *(t_cmd *)vptr_get(data->cmd, index);
	if (cmd.arg != NULL)
		builtin_type = builtin_get(cmd.arg[0]);
	else
		builtin_type = BUILTIN_NONE;
	if (redir(cmd, redirs) == EXIT_FAILURE)
		safe_exit(EXIT_FAILURE);
	if (redirs[PIPE_READ] != STDIN_FILENO && builtin_type == BUILTIN_NONE)
	{
		safe_dup2(redirs[PIPE_READ], STDIN_FILENO);
		safe_close(redirs[PIPE_READ]);
	}
	if (redirs[PIPE_WRITE] != STDOUT_FILENO && builtin_type == BUILTIN_NONE)
	{
		safe_dup2(redirs[PIPE_WRITE], STDOUT_FILENO);
		safe_close(redirs[PIPE_WRITE]);
	}
	safe_exit(safe_exec(data, cmd, redirs));
}
