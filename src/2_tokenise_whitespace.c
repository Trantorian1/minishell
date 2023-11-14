/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise_whitespace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:06:32 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:55:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_str.h"
#include "skip_whitespace.h"
#include "state_tokenise.h"
#include "tokenise_prev.h"
#include "tokenise_whitespace.h"
#include <stdlib.h>

static inline size_t	tokenise_whitespace_impl(
							t_vptr *_Nonnull dst,
							size_t i_curr,
							t_str str
							);

uint8_t	tokenise_whitespace(
	t_vptr *_Nonnull vptr,
	size_t *_Nonnull i,
	uint8_t *_Nonnull command,
	t_str input
) {
	if (vptr == NULL || i == NULL || command == NULL)
		return (EXIT_FAILURE);
	tokenise_prev(vptr, input, i[PREV], i[CURR]);
	i[CURR] = tokenise_whitespace_impl(vptr, i[CURR], input);
	i[PREV] = i[CURR];
	*command = true;
	return (EXIT_SUCCESS);
}

static inline size_t	tokenise_whitespace_impl(
	t_vptr *_Nonnull dst,
	size_t i_curr,
	t_str str
) {
	if (dst == NULL || str.len <= i_curr)
		return (str.len);
	i_curr = skip_whitespace(str, i_curr);
	vstr_append(dst, str_create(WHITESPACE));
	return (i_curr);
}
