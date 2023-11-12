/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:19:07 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 12:08:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_exec.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "dynamic/alloc.h"
#include "builtin_get.h"
#include "builtin.h"

#include "e_builtin.h"

uint8_t	safe_exec(t_data *_Nonnull data, t_cmd cmd)
{
	t_builtin	builtin_type;

	if (data == NULL)
		return (EXIT_FAILURE);

	if (cmd.arg[0] == NULL)
		return (EXIT_SUCCESS);

	builtin_type = builtin_get(cmd.arg[0]);

	// TODO: use execve !!!
	if (builtin_type != BUILTIN_NONE)
		return (builtin(data, cmd, builtin_type));
	else
		execv(cmd.arg[0], cmd.arg);

	safe_free_all();
	perror(cmd.arg[0]);
	exit(EXIT_FAILURE);
}
