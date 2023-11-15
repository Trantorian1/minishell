/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 05:46:54 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 15:17:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delimiter_get.h"

#include "d_str.h"

t_str	delimiter_get(t_vptr *_Nonnull redir, size_t i_curr)
{
	t_str	str_curr;
	t_str	delimiter;

	if (redir == NULL || i_curr >= redir->len)
		return (str_create(""));
	str_curr = *(t_str *)vptr_get(redir, i_curr);
	delimiter = str_create("");
	str_curr = *(t_str *)vptr_get(redir, i_curr);
	while (!str_eq(str_curr, WHITESPACE))
	{
		if (!str_eq(str_curr, QUOTE_DOUBLE) && !str_eq(str_curr, QUOTE_SINGLE))
			str_append_str(&delimiter, str_curr.get);
		vstr_rm(redir, i_curr);
		str_curr = *(t_str *)vptr_get(redir, i_curr);
	}
	return (delimiter);
}
