/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 06:54:46 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 09:13:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_display.h"
#include "state_tokenise.h"
#include "tokenise_quote.h"

#include <stdlib.h>

#include "dynamic/string.h"
#include "tokenise_prev.h"

#include "d_str.h"

static inline uint8_t	tokenise_quote_impl(
	t_vptr *_Nonnull vptr,
	size_t *_Nonnull i_curr,
	t_str input,
	char c
);

uint8_t	tokenise_quote(
	t_vptr *_Nonnull vptr,
	size_t *_Nonnull i,
	t_str input,
	char c
) {
	if (vptr == NULL || i == NULL)
		return (EXIT_FAILURE);

	tokenise_prev(vptr, input, i[PREV], i[CURR]);
	if (tokenise_quote_impl(vptr, &i[CURR], input, c))
		return (error_display("' or \"", "unterminated quote"));

	i[PREV] = i[CURR];
	return (EXIT_SUCCESS);
}

static inline uint8_t	tokenise_quote_impl(
	t_vptr *_Nonnull vptr,
	size_t *_Nonnull i_curr,
	t_str input,
	char c
) {
	size_t	i_curr_cpy;
	size_t	i_prev;
	t_cstr	quote;

	if (vptr == NULL || i_curr == NULL || input.len <= *i_curr)
		return (EXIT_FAILURE);

	if (c == '\'')
		quote = QUOTE_SINGLE;
	else if (c == '"')
		quote = QUOTE_DOUBLE;
	else
		return (EXIT_FAILURE);

	i_curr_cpy = *i_curr;
	i_prev = ++i_curr_cpy;
	while (input.get[i_curr_cpy] != '\0' && input.get[i_curr_cpy] != c)
		i_curr_cpy++;
	if (input.get[i_curr_cpy] == '\0')
		return (EXIT_FAILURE);

	vstr_append(vptr, str_create(quote));
	vstr_append(vptr, str_substr(input, i_prev, i_curr_cpy));
	vstr_append(vptr, str_create(quote));

	*i_curr = i_curr_cpy + 1;

	return (EXIT_SUCCESS);
}
