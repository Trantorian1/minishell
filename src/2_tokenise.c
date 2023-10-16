/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:37:00 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 15:51:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_str.h"
#include "state_tokenise.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <errno.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "dynamic/character.h"
// #include "dynamic/error.h"

#include "s_data.h"

static uint8_t	tokenise(
	t_str str,
	t_vptr *_Nonnull arg,
	t_vptr *_Nonnull redir
);

uint8_t	state_tokenise(t_data *_Nonnull data)
{
	t_str	line_curr;

	if (data == NULL)
		return (EXIT_FAILURE);

	data->arg = vptr_create(t_str, 0);
	data->redir = vptr_create(t_str, 0);

	line_curr = vptr_get(t_str, data->user_input, data->index_line);

	return (tokenise(line_curr, data->arg, data->redir));
}

static uint8_t	tokenise_quotation(
	t_str str,
	t_vptr *_Nonnull dst,
	size_t *_Nonnull ptr_curr,
	size_t *_Nonnull ptr_prev,
	char quote
) {
	t_cstr	quote_type;
	size_t	i_curr;
	size_t	i_prev;

	if (dst == NULL || ptr_curr == NULL || ptr_prev == NULL)
		return (EXIT_FAILURE);

	if (quote == '\'')
		quote_type = QUOTE_SINGLE;
	else
		quote_type = QUOTE_DOUBLE;

	i_prev = *ptr_prev + 1;
	i_curr = i_prev;

	while (str.get[i_curr] != '\0' && str.get[i_curr] != quote)
		i_curr++;
	if (str.get[i_curr] != quote)
		return (EXIT_FAILURE);

	vstr_append(dst, str_create(quote_type));
	vstr_append(dst, str_substr(str, i_prev, i_curr));
	vstr_append(dst, str_create(quote_type));

	*ptr_prev = i_curr + 1;
	*ptr_curr = i_curr + 1;

	return (EXIT_SUCCESS);
}

static uint8_t	tokenise_whitespace(
	t_str str,
	t_vptr *_Nonnull dst,
	size_t *_Nonnull ptr_curr,
	size_t *_Nonnull ptr_prev
) {
	size_t	i_curr;

	if (dst == NULL || ptr_curr == NULL || ptr_prev == NULL)
		return (EXIT_SUCCESS);

	// add whitespace token
	vstr_append(dst, str_create(WHITESPACE));

	// skips all sequantial whitespaces
	i_curr = *ptr_curr;
	while (is_whitespace(str.get[i_curr]))
		i_curr++;

	*ptr_prev = i_curr;
	*ptr_curr = i_curr;

	return (EXIT_SUCCESS);
}

static size_t	tokenise_redir(
	t_str str,
	t_vptr *_Nonnull redir,
	size_t *_Nonnull ptr_curr,
	size_t *_Nonnull ptr_prev
) {
	size_t	i_prev;
	size_t	i_curr;
	size_t	len_prev;
	
	if (redir == NULL || ptr_curr == NULL || ptr_prev == NULL)
		return (EXIT_FAILURE);

	// skips the redirection. If there still are redirection qualifiers ('<' or
	// '>') afterwards, then this is an invalid input.
	i_prev = *ptr_curr;
	i_curr = *ptr_curr + 1 + (str.get[*ptr_curr + 1] == str.get[*ptr_curr]);
	if (str.get[i_curr] == '<' || str.get[i_curr] == '>')
		return (EXIT_FAILURE);

	vstr_append(redir, str_substr(str, i_prev, i_curr));

	while (is_whitespace(str.get[i_curr]))
		i_curr++;

	len_prev = redir->len;

	// tokenises the redirection till a whitespace, a new redirection, the end
	// of the string or a pipe are encountered
	i_prev = i_curr;
	while (
		str.get[i_curr] != '\0' 
		&& !is_whitespace(str.get[i_curr])
		&& str.get[i_curr] != '<'
		&& str.get[i_curr] != '>'
		&& str.get[i_curr] != '|'
	) {
		if (
			str.get[i_curr] == '\'' 
			&& tokenise_quotation(str, redir, &i_curr, &i_prev, '\'')
		)
			return (EXIT_FAILURE);

		else if (
			str.get[i_curr] == '"'
			&& tokenise_quotation(str, redir, &i_curr, &i_prev, '"')
		)
			return (EXIT_FAILURE);

		else
			i_curr++;
	}

	// adds any trailing input at the end of the redirection (ex: 'tes't)
	if (i_prev != i_curr)
		vstr_append(redir, str_substr(str, i_prev, i_curr));

	if (len_prev == redir->len)
		return (EXIT_FAILURE);

	vstr_append(redir, str_create(WHITESPACE));
	
	while (is_whitespace(str.get[i_curr]))
		i_curr++;
	
	*ptr_prev = i_curr;
	*ptr_curr = i_curr;

	return (EXIT_SUCCESS);
}

static uint8_t	tokenise_pipe(
	t_str str,
	t_vptr *_Nonnull arg,
	t_vptr *_Nonnull redir,
	size_t *_Nonnull ptr_curr,
	size_t *_Nonnull ptr_prev
) {
	size_t	i_curr;
	
	if (arg == NULL || redir == NULL || ptr_curr == NULL || ptr_prev == NULL)
		return (EXIT_FAILURE);

	vstr_append(arg, str_create(PIPE));
	vstr_append(redir, str_create(PIPE));

	i_curr = *ptr_curr + 1;
	while (is_whitespace(str.get[i_curr]))
		i_curr++;

	*ptr_prev = i_curr;
	*ptr_curr = i_curr;

	return (EXIT_SUCCESS);
}

static uint8_t	save_prev(
	t_str str,
	t_vptr *_Nonnull dst,
	size_t *_Nonnull ptr_curr,
	size_t *_Nonnull ptr_prev
) {
	size_t	index_prev;
	size_t	i_curr;

	if (dst == NULL || ptr_curr == NULL || ptr_prev == NULL)
		return (EXIT_FAILURE);

	index_prev = *ptr_prev;
	i_curr = *ptr_curr;

	if (index_prev != i_curr)
		vstr_append(dst, str_substr(str, index_prev, i_curr));
	
	*ptr_prev = i_curr;
	return (EXIT_SUCCESS);
}

static uint8_t	tokenise(
	t_str str,
	t_vptr *_Nonnull arg,
	t_vptr *_Nonnull redir
) {
	size_t	i_prev;
	size_t	i_curr;

	if (arg == NULL || redir == NULL)
		return (EXIT_FAILURE);

	i_prev = 0;
	while (is_whitespace(str.get[i_prev]))
		i_prev++;

	i_curr = i_prev;
	while (str.get[i_curr] != '\0')
	{
		if (str.get[i_curr] == '\'')
		{
			if (save_prev(str, arg, &i_curr, &i_prev))
				return (EXIT_FAILURE);
			if (tokenise_quotation(str, arg, &i_curr, &i_prev, '\''))
				return (EXIT_FAILURE);
		}

		else if (str.get[i_curr] == '"')
		{
			if (save_prev(str, arg, &i_curr, &i_prev))
				return (EXIT_FAILURE);
			if (tokenise_quotation(str, arg, &i_curr, &i_prev, '"'))
				return (EXIT_FAILURE);
		}
		
		else if (is_whitespace(str.get[i_curr]))
		{
			if (save_prev(str, arg, &i_curr, &i_prev))
				return (EXIT_FAILURE);
			if (tokenise_whitespace(str, arg, &i_curr, &i_prev))	
				return (EXIT_FAILURE);
		}

		else if (str.get[i_curr] == '<' || str.get[i_curr] == '>')
		{
			if (save_prev(str, arg, &i_curr, &i_prev))
				return (EXIT_FAILURE);
			if (tokenise_redir(str, redir, &i_curr, &i_prev))
				return (EXIT_FAILURE);
		}

		else if (str.get[i_curr] == '|')
		{
			if (save_prev(str, arg, &i_curr, &i_prev))
				return (EXIT_FAILURE);
			if (tokenise_pipe(str, arg, redir, &i_curr, &i_prev))
				return (EXIT_FAILURE);
		}

		else
			i_curr++;
	}

	if (i_prev != i_curr)
		vstr_append(arg, str_substr(str, i_prev, i_curr));

	if (
		str_eq(vptr_last(t_str, arg), PIPE) 
		&& str_eq(vptr_last(t_str, redir), PIPE)
	) {
		printf(ERR_PIPE);
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

