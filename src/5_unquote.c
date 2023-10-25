/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_unquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 22:44:23 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 18:47:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_unquote.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "d_str.h"

static uint8_t	unquote_impl(t_vptr *_Nonnull vstr);

uint8_t	state_unquote(t_data *_Nonnull data)
{
	if (data == NULL)
		return (EXIT_FAILURE);

	if (unquote_impl(data->arg) || unquote_impl(data->redir))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

static size_t	vstr_unquote(t_vptr *_Nonnull vstr, size_t index)
{
	t_str	content;
	t_str	str_curr;

	if (vstr == NULL)
		return (EXIT_FAILURE);

	content = str_create("");
	str_curr = vptr_get(t_str, vstr, index);
	while (
		index < vstr->len
		&& !str_eq(str_curr, WHITESPACE) 
		&& !str_eq(str_curr, PIPE)
	) {
		if (!str_eq(str_curr, QUOTE_SINGLE) && !str_eq(str_curr, QUOTE_DOUBLE))
			str_append_str(&content, vptr_get(t_str, vstr, index).get);

		vstr_rm(vstr, index);
		str_curr = vptr_get(t_str, vstr, index);
	}
	vstr_insert(vstr, content, index);

	return (EXIT_SUCCESS);
}

static uint8_t	unquote_impl(t_vptr *_Nonnull vstr)
{
	size_t	index;
	t_str	str;

	if (vstr == NULL)
		return (EXIT_FAILURE);

	index = 0;
	while (index < vstr->len)
	{
		str = vptr_get(t_str, vstr, index);
		if (str_eq(str, QUOTE_SINGLE) || str_eq(str, QUOTE_DOUBLE))
			vstr_unquote(vstr, index);
		if (str_eq(str, WHITESPACE))
			vstr_rm(vstr, index);
		else
			index++;
	}
	
	return (EXIT_SUCCESS);
}
