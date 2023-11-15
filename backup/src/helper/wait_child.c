/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:06:26 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:43:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wait_child.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int32_t	decode_status(int32_t status);

uint8_t	wait_child(pid_t pid_last)
{
	pid_t	pid;
	int32_t	status;
	uint8_t	status_last;

	status_last = EXIT_SUCCESS;
	while (true)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			break ;
		else if (pid == pid_last)
			status_last = (uint8_t)decode_status(status);
	}
	return (status_last);
}

static int32_t	decode_status(int32_t status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			write(STDERR_FILENO, "minishell: child: core dump\n", 29);
		status = WTERMSIG(status) + 128;
	}
	return (status);
}
