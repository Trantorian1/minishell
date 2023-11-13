/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:39:06 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_expand.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "dynamic/character.h"
#include "env_get.h"
#include "d_str.h"

static uint8_t	expand_impl(t_vptr *_Nonnull vptr, t_vptr *_Nonnull env, uint8_t exit_code);

uint8_t	state_expand(t_data *_Nonnull data)
{
	if (data == NULL)
		return (EXIT_FAILURE);

	if (
		expand_impl(data->arg, data->env, data->exit_code) 
		|| expand_impl(data->redir, data->env, data->exit_code)
	) {
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

static bool	is_legal_var_char(char c)
{
	return (is_letter(c) || is_digit(c) || c == '_');
}

static uint8_t	expand_string(t_str *_Nonnull str, t_vptr *_Nonnull env, uint8_t exit_code)
{
	size_t	i_prev;
	size_t	i_curr;
	t_str	var;

	if (str == NULL || env == NULL)
		return (EXIT_FAILURE);

	i_prev = str_find_char(*str, '$');
	if (i_prev == str->len)
		return (EXIT_SUCCESS);

	i_curr = i_prev + 1;

	while (is_legal_var_char(str->get[i_curr]))
		i_curr++;

	if (str->get[i_curr] == '?')
	{
		var = ui8_to_str(exit_code);
		str_rm(str, i_prev, i_curr + 1);
		str_insert_str(str, var.get, i_prev);
		str_destroy(&var);
	}
	else
	{
		var = str_substr(*str, i_prev + 1, i_curr);
		str_rm(str, i_prev, i_curr);
		str_insert_str(str, env_get(env, var.get).get, i_prev);
	}

	return (EXIT_SUCCESS);
}

static uint8_t	expand_impl(t_vptr *_Nonnull vptr, t_vptr *_Nonnull env, uint8_t exit_code)
{
	size_t	index;
	t_str	*str;

	if (vptr == NULL)
		return (EXIT_FAILURE);

	index = 0;
	while (index < vptr->len)
	{
		str = vptr_get_ptr(t_str, vptr, index);

		if (str_eq(*str, QUOTE_SINGLE))
			index += 2;
		else
		{
			if (expand_string(str, env, exit_code))
				return (EXIT_FAILURE);
			index++;
		}
	}

	return (EXIT_FAILURE);
}
