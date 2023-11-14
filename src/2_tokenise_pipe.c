/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 07:34:17 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 09:12:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_str.h"
#include "tokenise_pipe.h"

#include <stdlib.h>

#include "error_display.h"
#include "state_tokenise.h"
#include "skip_whitespace.h"

static inline size_t	tokenise_pipe_impl(
	t_vptr *_Nonnull arg,
	t_vptr *_Nonnull redir,
	t_str str,
	size_t i_curr
);

uint8_t	tokenise_pipe(
	t_data *_Nonnull data,
	size_t *_Nonnull i,
	uint8_t *_Nonnull command,
	t_str input
) {
	if (i[PREV] == i[CURR] && command == false)
		return (error_display("pipe", "unterminated pipe"));
	i[CURR] = tokenise_pipe_impl(data->arg, data->redir, input, i[CURR]);
	i[PREV] = i[CURR];
	command = false;
	return (EXIT_SUCCESS);
}

static inline size_t	tokenise_pipe_impl(
	t_vptr *_Nonnull arg,
	t_vptr *_Nonnull redir,
	t_str str,
	size_t i_curr
) {
	if (arg == NULL || redir == NULL || str.len <= i_curr)
		return (str.len);

	vstr_append(arg, str_create(PIPE));
	vstr_append(redir, str_create(PIPE));

	return (skip_whitespace(str, i_curr + 1));
}
