/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:19:07 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:42:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_exec.h"

#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "d_pipe.h"
#include "dynamic/alloc.h"
#include "builtin_get.h"
#include "builtin.h"
#include "env_collect.h"
#include "safe_exit.h"
#include "error_display.h"

#include "e_builtin.h"
#include "d_err_codes.h"

uint8_t	safe_exec(
	t_data *_Nonnull data,
	t_cmd cmd,
	int32_t *_Nonnull pipe_fd
) {
	t_builtin	builtin_type;

	if (data == NULL)
		return (EXIT_FAILURE);
	if (cmd.arg[0] == NULL)
		return (EXIT_SUCCESS);
	builtin_type = builtin_get(cmd.arg[0]);
	if (builtin_type != BUILTIN_NONE)
		return (builtin(data, cmd, pipe_fd, true));
	else
		execve(cmd.arg[0], cmd.arg, env_collect(data->env));
	error_display(cmd.arg[0], "command not found");
	safe_exit(ENOTFOUD);
}
