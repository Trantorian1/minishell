/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:53:38 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_pwd.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "dynamic/string.h"

#include "d_pipe.h"

uint8_t	builtin_pwd(t_data *_Nonnull data, t_cmd cmd, int32_t *_Nonnull pipe_fd)
{
	char	cwd[2048];

	(void)data;
	(void)cmd;

	if (getcwd(cwd, 2048) == NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}

	write(pipe_fd[PIPE_WRITE], cwd, cstr_len(cwd));
	write(pipe_fd[PIPE_WRITE], "\n", 1);

	return (EXIT_SUCCESS);
}
