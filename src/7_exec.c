/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:04:00 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 16:59:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_exec.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"

#include "safe_fork.h"
#include "safe_pipe.h"
#include "safe_dup2.h"
#include "safe_close.h"

#include "s_cmd.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

uint8_t	state_exec(t_data *_Nonnull data)
{
	size_t	index;
	int32_t	read_fd;
	int32_t	pipe_id[2];
	t_cmd	cmd;

	if (data == NULL)
		return (EXIT_FAILURE);

	index = 0;
	read_fd = STDIN_FILENO;

	while (index < data->cmd->len)
	{
		safe_pipe(pipe_id);

		if (safe_fork() == 0)
		{
			safe_close(pipe_id[PIPE_READ]);

			safe_dup2(read_fd, STDIN_FILENO);
			safe_close(read_fd);

			if (index != data->cmd->len - 1)
			{
				safe_dup2(pipe_id[PIPE_WRITE], STDOUT_FILENO);
				safe_close(pipe_id[PIPE_WRITE]);
			}

			cmd = vptr_get(t_cmd, data->cmd, index);
			execv(cmd.arg[0], cmd.arg);

			perror("command not found");
			exit(EXIT_FAILURE);
		}
		else
		{
			safe_close(read_fd);
			safe_close(pipe_id[PIPE_WRITE]);
			read_fd = pipe_id[PIPE_READ];
		}

		index++;
	}

	return (EXIT_SUCCESS);
}
