/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:42:46 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 06:49:09 by marvin           ###   ########.fr       */
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

#include "d_str.h"

static uint8_t	tokenise_impl(
	t_vptr *_Nonnull arg, 
	t_vptr *_Nonnull redir, 
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

	if (tokenise_impl(data->arg, data->redir, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	data->index_line++;

	return (EXIT_SUCCESS);
}

static size_t	skip_whitespace(
	t_str str,
	size_t i_curr
) {
	if (str.len <= i_curr)
		return (str.len);

	while (str.get[i_curr] != '\0' && is_whitespace(str.get[i_curr]))
		i_curr++;

	return (i_curr);
}

static uint8_t	tokenise_quote(
	t_vptr *_Nonnull dst,
	t_str str,
	size_t *store,
	char c
) {
	size_t	i_curr;
	size_t	i_prev;
	t_cstr	quote;

	if (dst == NULL || str.len <= *store)
		return (EXIT_FAILURE);

	if (c == '\'')
		quote = QUOTE_SINGLE;
	else if (c == '"')
		quote = QUOTE_DOUBLE;
	else
		return (EXIT_FAILURE);

	i_curr = *store;
	i_prev = ++i_curr;
	while (str.get[i_curr] != '\0' && str.get[i_curr] != c)
		i_curr++;
	if (str.get[i_curr] == '\0')
		return (EXIT_FAILURE);

	vstr_append(dst, str_create(quote));
	vstr_append(dst, str_substr(str, i_prev, i_curr));
	vstr_append(dst, str_create(quote));

	*store = i_curr + 1;

	return (EXIT_SUCCESS);
}

static size_t	tokenise_whitespace(
	t_vptr *_Nonnull dst,
	t_str str,
	size_t i_curr
) {
	if (dst == NULL || str.len <= i_curr)
		return (str.len);

	i_curr = skip_whitespace(str, i_curr);
	vstr_append(dst, str_create(WHITESPACE));

	return (i_curr);
}

static size_t	tokenise_pipe(
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

static uint8_t	save_prev(
	t_vptr *_Nonnull dst,
	t_str str,
	size_t i_prev,
	size_t i_curr
) {
	if (dst == NULL)
		return (EXIT_FAILURE);

	if (i_prev != i_curr)
		vstr_append(dst, str_substr(str, i_prev, i_curr));

	return (EXIT_SUCCESS);
}

static uint8_t	tokenise_redir(
	t_vptr *_Nonnull redir,
	t_str input,
	size_t *_Nonnull store
) {
	size_t	i_curr;
	size_t	i_prev;
	size_t	len;
	bool	command;

	if (redir == NULL || store == NULL || *store + 1 >= input.len)
		return (EXIT_FAILURE);

	len = 1 + (input.get[*store] == input.get[*store + 1]);
	if (input.get[*store + len] == '>' || input.get[*store + len] == '<')
		return (error_display("redir", "invalid redirection"));

	vstr_append(redir, str_substr(input, *store, *store + len));
	vstr_append(redir, str_create(WHITESPACE));

	i_curr = skip_whitespace(input, *store + len);
	i_prev = i_curr;
	command = false;

	while (
		input.get[i_curr] != '\0'
		&& input.get[i_curr] != '<'
		&& input.get[i_curr] != '>'
		&& input.get[i_curr] != '|'
		&& !is_whitespace(input.get[i_curr])
	) {
		if (input.get[i_curr] == '\'')
		{
			save_prev(redir, input, i_prev, i_curr);
			if(tokenise_quote(redir, input, &i_curr, '\'') == EXIT_FAILURE)
				return (error_display("'", "unterminated quote"));
			i_prev = i_curr;
			command = true;
		}
		else if (input.get[i_curr] == '"')
		{
			save_prev(redir, input, i_prev, i_curr);
			if(tokenise_quote(redir, input, &i_curr, '"') == EXIT_FAILURE)
				return (error_display("\"", "unterminated quote"));
			i_prev = i_curr;
			command = true;
		}
		else if (input.get[i_curr] == '|')
		{
			if (i_prev == i_curr && command == false)
				return (error_display("pipe", "unterminated pipe"));
			save_prev(redir, input, i_prev, i_curr);
			i_curr = tokenise_pipe(redir, redir, input, i_curr);
			i_prev = i_curr;
			command = false;
		}
		else if (is_whitespace(input.get[i_curr]))
		{
			save_prev(redir, input, i_prev, i_curr);
			i_curr = tokenise_whitespace(redir, input, i_curr);
			i_prev = i_curr;
			command = true;
		}
		else
			i_curr++;
	}
	save_prev(redir, input, i_prev, i_curr);
	vstr_append(redir, str_create(WHITESPACE));
	*store = i_curr;

	return (EXIT_SUCCESS);
}

static uint8_t	tokenise_impl(
	t_vptr *_Nonnull arg, 
	t_vptr *_Nonnull redir, 
	t_str input
) {
	size_t	i_prev;
	size_t	i_curr;
	uint8_t	command;

	if (arg == NULL || redir == NULL)
		return (EXIT_FAILURE);

	i_prev = 0;
	i_curr = 0;
	command = false;
	while (i_curr < input.len)
	{
		if (input.get[i_curr] == '\'')
		{
			save_prev(arg, input, i_prev, i_curr);
			if(tokenise_quote(arg, input, &i_curr, '\'') == EXIT_FAILURE)
				return (error_display("'", "unterminated quote"));
			i_prev = i_curr;
			command = true;
		}
		else if (input.get[i_curr] == '"')
		{
			save_prev(arg, input, i_prev, i_curr);
			if(tokenise_quote(arg, input, &i_curr, '"') == EXIT_FAILURE)
				return (error_display("\"", "unterminated quote"));
			i_prev = i_curr;
			command = true;
		}
		else if (input.get[i_curr] == '|')
		{
			if (i_prev == i_curr && command == false)
				return (error_display("pipe", "unterminated pipe"));
			save_prev(arg, input, i_prev, i_curr);
			i_curr = tokenise_pipe(arg, redir, input, i_curr);
			i_prev = i_curr;
			command = false;
		}
		else if (input.get[i_curr] == '>' || input.get[i_curr] == '<')
		{
			save_prev(arg, input, i_prev, i_curr);
			if (tokenise_redir(redir, input, &i_curr) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i_prev = i_curr;
			command = true;
		}
		else if (is_whitespace(input.get[i_curr]))
		{
			save_prev(arg, input, i_prev, i_curr);
			i_curr = tokenise_whitespace(arg, input, i_curr);
			i_prev = i_curr;
			command = true;
		}
		else
			i_curr++;
	}
	save_prev(arg, input, i_prev, i_curr);

	if (str_eq(vptr_get(t_str, arg, arg->len - 1), PIPE))
		return (error_display("pipe", "unterminated pipe"));
	return (EXIT_SUCCESS);
}
