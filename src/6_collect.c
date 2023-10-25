/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_collect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 01:00:05 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 16:57:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	size_t	i_prev;
	size_t	i_curr;
	t_str	exec;
	t_cmd	cmd;

	if (data == NULL)
		return (EXIT_FAILURE);

	exec = get_exec_path(data->env, vptr_get(t_str, data->arg, 0).get);
	vstr_replace(data->arg, exec, 0);

	i_prev = 0;
	i_curr = 0;
	while (i_curr < data->arg->len)
	{
		if (str_eq(vptr_get(t_str, data->arg, i_curr), PIPE))
		{
			cmd.arg = collect(data->arg, i_prev);
			vptr_append(data->cmd, &cmd);
			i_prev = i_curr + 1;

			exec = get_exec_path(data->env, vptr_get(t_str, data->arg, i_prev).get);
			vstr_replace(data->arg, exec, i_prev);
		}
		i_curr++;
	}
	cmd.arg = collect(data->arg, i_prev);
	vptr_append(data->cmd, &cmd);

	return (EXIT_SUCCESS);
}

static uint8_t	collect_redir(t_data *_Nonnull data)
{
	size_t	i_prev;
	size_t	i_curr;
	t_cmd	*cmd;

	if (data == NULL)
		return (EXIT_FAILURE);

	i_prev = 0;
	i_curr = 0;
	cmd = vptr_get_ptr(t_cmd, data->cmd, 0);

	while (i_curr < data->redir->len)
	{
		if (str_eq(vptr_get(t_str, data->redir, i_curr), PIPE))
		{
			cmd->redir = collect(data->redir, i_prev);
			cmd++;
			i_prev = i_curr + 1;
		}
		i_curr++;
	}
	cmd->redir = collect(data->redir, i_prev);

	return (EXIT_SUCCESS);
}
