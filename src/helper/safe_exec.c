/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:19:07 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 16:16:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_exec.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "dynamic/alloc.h"
#include "builtin_get.h"
#include "builtin.h"
#include "env_collect.h"

#include "e_builtin.h"
#include "safe_exit.h"

uint8_t	safe_exec(t_data *_Nonnull data, t_cmd cmd)
{
	t_builtin	builtin_type;

	if (data == NULL)
		return (EXIT_FAILURE);

	if (cmd.arg[0] == NULL)
		return (EXIT_SUCCESS);

	builtin_type = builtin_get(cmd.arg[0]);

	if (builtin_type != BUILTIN_NONE)
		return (builtin(data, cmd, builtin_type));
	else
		execve(cmd.arg[0], cmd.arg, env_collect(data->env));

	perror(cmd.arg[0]);
	safe_exit(EXIT_FAILURE);
}
