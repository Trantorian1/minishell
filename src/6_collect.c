/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_collect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 01:00:05 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 21:21:41 by marvin           ###   ########.fr       */
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
	data->cmd = vptr_create(sizeof(t_cmd), 0);
	if (collect_arg(data) || collect_redir(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_cstr *_Nullable	collect(t_vptr *_Nonnull vptr, size_t icur)
{
	size_t	i_prev;
	t_cstr	*arg;

	if (vptr == NULL || icur > vptr->len)
		return (NULL);
	i_prev = icur;
	while (icur < vptr->len && !str_eq(*(t_str *)vptr_get(vptr, icur), PIPE))
		icur++;
	arg = safe_alloc(sizeof(*arg) * (icur - i_prev + 1));
	arg[icur - i_prev] = NULL;
	while (icur > i_prev)
	{
		arg[icur - i_prev - 1] = (*(t_str *)vptr_get(vptr, icur - 1)).get;
		icur--;
	}
	return (arg);
}

static uint8_t	collect_arg(t_data *_Nonnull data)
{
	t_vptr	*arg;
	size_t	i;
	t_str	exec;
	t_cmd	cmd;

	if (data == NULL)
		return (EXIT_FAILURE);
	if (data->arg->len == 0)
		vptr_append(data->cmd, (t_cmd []){(t_cmd){NULL, NULL}});
	arg = data->arg;
	i = 0;
	while (i < data->arg->len)
	{
		exec = *(t_str *)vptr_get(arg, i);
		if (builtin_get(exec.get) == BUILTIN_NONE)
			vstr_replace(arg, get_exec_path(data->env, exec.get), i);
		cmd.arg = collect(arg, i);
		vptr_append(data->cmd, &cmd);
		while (i < arg->len && !str_eq(*(t_str *)vptr_get(arg, i), PIPE))
			i++;
		i++;
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
	cmd = (t_cmd *)vptr_get(data->cmd, 0);
	cmd->redir = vptr_create(sizeof(t_str), 0);
	while (i_curr < data->redir->len)
	{
		str = *(t_str *)vptr_get(data->redir, i_curr);
		if (str_eq(str, PIPE))
		{
			cmd++;
			cmd->redir = vptr_create(sizeof(t_str), 0);
		}
		else
			vstr_append(cmd->redir, str_create(str.get));
		i_curr++;
	}
	return (EXIT_SUCCESS);
}
