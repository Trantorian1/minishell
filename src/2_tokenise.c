/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:42:46 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 09:21:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_tokenise.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "dynamic/character.h"
#include "error_display.h"
#include "tokenise_pipe.h"
#include "tokenise_prev.h"
#include "tokenise_quote.h"

#include "d_str.h"
#include "tokenise_redir.h"
#include "tokenise_whitespace.h"

static inline uint8_t	tokenise_arg(
	t_data *_Nonnull data, 
	t_str input
);

uint8_t	state_tokenise(t_data *_Nonnull data)
{
	t_str	line;

	if (data == NULL)
		return (EXIT_FAILURE);

	line = vptr_get(t_str, data->user_input, data->index_line);

	data->arg = vptr_create(t_str, 0);
	data->redir = vptr_create(t_str, 0);

	if (tokenise_arg(data, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	data->index_line++;

	return (EXIT_SUCCESS);
}

static inline uint8_t	tokenise_arg(
	t_data *_Nonnull data, 
	t_str input
) {
	size_t	i[2];
	uint8_t	command;

	if (data == NULL)
		return (EXIT_FAILURE);

	i[PREV] = 0;
	i[CURR] = 0;
	command = false;
	while (i[CURR] < input.len)
	{
		if (input.get[i[CURR]] == '\'' || input.get[i[CURR]] == '"')
		{
			if (tokenise_quote(data->arg, i, input, input.get[i[CURR]]))
				return (EXIT_FAILURE);
			command = true;
		}
		else if (input.get[i[CURR]] == '|')
		{
			if (tokenise_pipe(data, i, &command, input))
				return (EXIT_FAILURE);
		}
		else if (input.get[i[CURR]] == '>' || input.get[i[CURR]] == '<')
		{
			if (tokenise_redir(data, i, &command, input))
				return (EXIT_FAILURE);
		}
		else if (is_whitespace(input.get[i[CURR]]))
		{
			if (tokenise_whitespace(data->arg, i, &command, input))
				return (EXIT_FAILURE);
		}
		else
			i[CURR]++;
	}
	tokenise_prev(data->arg, input, i[PREV], i[CURR]);

	if (str_eq(vptr_get(t_str, data->arg, data->arg->len - 1), PIPE))
		return (error_display("pipe", "unterminated pipe"));
	return (EXIT_SUCCESS);
}
