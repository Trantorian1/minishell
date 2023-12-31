/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_collect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 01:00:05 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 06:37:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr_str_destroy.h"
#include "builtin_get.h"
#include "e_builtin.h"
#include "state_collect.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "dynamic/alloc.h"
#include "get_exec_path.h"

#include "d_str.h"
#include "s_cmd.h"

static uint8_t	collect_arg(t_data *_Nonnull data);
static uint8_t	collect_redir(t_data *_Nonnull data);

uint8_t	state_collect(t_data *_Nonnull data)
{
	if (data == NULL)
		return (EXIT_FAILURE);

	data->cmd = vptr_create(t_cmd, 0);
	if (collect_arg(data) || collect_redir(data))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

static t_cstr *_Nullable	collect(t_vptr *_Nonnull vptr, size_t i_curr)
{
	size_t	i_prev;
	t_cstr	*arg;

	if (vptr == NULL || i_curr > vptr->len)
		return (NULL);

	i_prev = i_curr;
	while (i_curr < vptr->len && !str_eq(vptr_get(t_str, vptr, i_curr), PIPE))
		i_curr++;

	arg = safe_alloc(sizeof(*arg) * (i_curr - i_prev + 1));
	arg[i_curr - i_prev] = NULL;

	while (i_curr > i_prev)
	{
		arg[i_curr - i_prev - 1] = vptr_get(t_str, vptr, i_curr - 1).get;
		i_curr--;
	}

	return (arg);
}

static uint8_t	collect_arg(t_data *_Nonnull data)
{
	t_vptr	*arg;
	size_t	index;
	t_str	exec;
	t_cmd	cmd;

	if (data == NULL)
		return (EXIT_FAILURE);

	arg = data->arg;
	index = 0;
	while (index < data->arg->len)
	{
		exec = vptr_get(t_str, arg, index);
		if (builtin_get(exec.get) == BUILTIN_NONE)
			vstr_replace(arg, get_exec_path(data->env, exec.get), index);

		cmd.arg = collect(arg, index);
		vptr_append(data->cmd, &cmd);

		while (index < arg->len && !str_eq(vptr_get(t_str, arg, index), PIPE))
			index++;

		index++;
	}

	return (EXIT_SUCCESS);
}

static uint8_t	collect_redir(t_data *_Nonnull data)
{
	size_t	i_curr;
	t_cmd	*cmd;
	t_str	str;

	if (data == NULL)
		return (EXIT_FAILURE);

	i_curr = 0;
	cmd = vptr_get_ptr(t_cmd, data->cmd, 0);
	cmd->redir = vptr_create(t_str, 0);

	while (i_curr < data->redir->len)
	{
		str = vptr_get(t_str, data->redir, i_curr);
		if (str_eq(str, PIPE))
		{
			cmd++;
			cmd->redir = vptr_create(t_str, 0);
		}
		else
			vstr_append(cmd->redir, str_create(str.get));
		i_curr++;
	}

	return (EXIT_SUCCESS);
}
