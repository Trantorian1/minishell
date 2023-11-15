/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:41:32 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 18:19:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_str.h"
#include "dynamic/character.h"
#include "error_display.h"
#include "s_data.h"
#include "skip_whitespace.h"
#include "state_tokenise.h"
#include "tokenise_pipe.h"
#include "tokenise_prev.h"
#include "tokenise_quote.h"
#include "tokenise_redir.h"
#include "tokenise_whitespace.h"
#include <stdlib.h>

static inline uint8_t	tokenise_redir_impl(t_data *_Nonnull data,
							size_t *_Nonnull store, t_str input);

uint8_t	tokenise_redir(
	t_data *_Nonnull data,
	size_t *_Nonnull i,
	uint8_t *_Nonnull command,
	t_str input
) {
	if (data == NULL || i == NULL || command == NULL)
		return (EXIT_FAILURE);
	tokenise_prev(data->arg, input, i[PREV], i[CURR]);
	if (tokenise_redir_impl(data, &i[CURR], input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i[PREV] = i[CURR];
	*command = true;
	return (EXIT_SUCCESS);
}

static inline bool	should_loop(t_str input, size_t *_Nonnull i)
{
	if (i == NULL)
		return (false);
	return (input.get[i[CURR]] != '\0'
		&& input.get[i[CURR]] != '<'
		&& input.get[i[CURR]] != '>'
		&& input.get[i[CURR]] != '|'
		&& !is_whitespace(input.get[i[CURR]]));
}

static inline uint8_t	redir_loop(
	t_str input,
	uint8_t *_Nonnull command,
	size_t *_Nonnull i,
	t_data *_Nonnull data
) {
	if (input.get[i[CURR]] == '\'' || input.get[i[CURR]] == '"')
	{
		if (tokenise_quote(data->redir, i, input, input.get[i[CURR]]))
			return (EXIT_FAILURE);
		*command = true;
	}
	else
		i[CURR]++;
	return (EXIT_SUCCESS);
}

static inline uint8_t	tokenise_redir_impl(
	t_data *_Nonnull data,
	size_t *_Nonnull store,
	t_str input
) {
	size_t	len;
	size_t	i[2];
	uint8_t	command;

	if (data->redir == NULL || store == NULL || *store + 1 >= input.len)
		return (error_display("redir", "no content to redirection"));
	len = 1 + (input.get[*store] == input.get[*store + 1]);
	if (input.get[*store + len] == '>' || input.get[*store + len] == '<')
		return (error_display("redir", "invalid redirection"));
	vstr_append(data->redir, str_substr(input, *store, *store + len));
	vstr_append(data->redir, str_create(WHITESPACE));
	i[CURR] = skip_whitespace(input, *store + len);
	i[PREV] = i[CURR];
	command = false;
	while (should_loop(input, i))
	{
		if (redir_loop(input, &command, i, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (command == false && i[PREV] == i[CURR])
		return (error_display("redir", "no content to redirection"));
	tokenise_prev(data->redir, input, i[PREV], i[CURR]);
	vstr_append(data->redir, str_create(WHITESPACE));
	*store = i[CURR];
	return (EXIT_SUCCESS);
}
