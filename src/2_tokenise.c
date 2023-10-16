/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:39:54 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 14:12:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:37:00 by marvin            #+#    #+#             */
/*   Updated: 2023/09/27 22:58:31 by marvin           ###   ########.fr       */
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
#include "dynamic/error.h"

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
	char	*quote_type;
	size_t	i_prev;
	size_t	i_curr;

	// if (str == NULL || dst == NULL || ptr_curr == NULL || ptr_prev == NULL)
	// 	return (fail_at("tokenise_quotation", EINVAL));

	if (quote == '\'')
		quote_type = QUOTE_SINGLE;
	else if (quote == '"')
		quote_type = QUOTE_DOUBLE;
	else
		return (EXIT_FAILURE);

	i_prev = *ptr_prev;
	i_curr = *ptr_curr;

	// surrounds string by quote tokens for distinction between single and
	// double quotes
	if (i_curr != i_prev)
		vstr_append(dst, str_substr(str, i_prev, i_curr));

	// combine sequantial quotations of the same type to reduce parsing
	// complexity at later stages of the program
	vstr_append(dst, str_create(quote_type));

	// checks for quote termination
	i_prev = ++i_curr;
	while (str.get[i_curr] != '\0' && str.get[i_curr] != quote)
		i_curr++;
	if (str.get[i_curr] != quote)
		return ((void)printf(ERR_STR, i_prev - 1), EXIT_FAILURE);

	vstr_append(dst, str_substr(str, i_prev, i_curr));
	i_prev = ++i_curr;

	// surrounds string by quote tokens for distinction between single and
	// double quotes
	vstr_append(dst, str_create(quote_type));

	*ptr_prev = i_prev;
	*ptr_curr = i_curr;
	return (EXIT_SUCCESS);
}

// static uint8_t	tokenise_whitespace(
// 	char *_Nonnull cstr,
// 	t_arr_str *_Nonnull dst,
// 	size_t *_Nonnull ptr_curr,
// 	size_t *_Nonnull ptr_prev
// ) {
// 	size_t	index_curr;
// 	size_t	index_prev;
//
// 	if (cstr == NULL || ptr_curr == NULL || ptr_prev == NULL)
// 		return (fail_at("tokenise_whitespace", EINVAL));
//
// 	// add whitespace token
// 	arr_str_append(dst, NULL);
// 	str_append(dst->last, WHITESPACE);
//
// 	// skips all sequantial whitespaces
// 	index_curr = *ptr_curr;
// 	while (is_whitespace(cstr[index_curr]))
// 		index_curr++;
// 	index_prev = index_curr;
//
// 	*ptr_prev = index_prev;
// 	*ptr_curr = index_curr;
//
// 	return (EXIT_SUCCESS);
// }
//
// static size_t	tokenise_redir(
// 	char *_Nonnull cstr,
// 	t_arr_str *_Nonnull redir,
// 	size_t *_Nonnull ptr_curr,
// 	size_t *_Nonnull ptr_prev
// ) {
// 	size_t	index_prev;
// 	size_t	index_curr;
// 	size_t	len_prev;
// 	
// 	if (cstr == NULL || redir == NULL || ptr_curr == NULL || ptr_prev == NULL)
// 		return (fail_at("tokenise_redir", EINVAL));
//
// 	// skips the redirection. If there still are redirection qualifiers ('<' or
// 	// '>') afterwards, then this is an invalid input.
// 	index_prev = *ptr_curr;
// 	index_curr = *ptr_curr + 1 + (cstr[*ptr_curr + 1] == cstr[*ptr_curr]);
// 	if (cstr[index_curr] == '<' || cstr[index_curr] == '>')
// 		return ((void)printf(ERR_REDIR, index_curr), EXIT_FAILURE);
//
// 	arr_str_append(redir, NULL);
// 	str_append_range(redir->last, cstr, index_prev, index_curr);
//
// 	while (is_whitespace(cstr[index_curr]))
// 		index_curr++;
//
// 	len_prev = redir->len;
//
// 	// tokenises the redirection till a whitespace, a new redirection, the end
// 	// of the string or a pipe are encountered
// 	index_prev = index_curr;
// 	while (
// 		cstr[index_curr] != '\0' 
// 		&& !is_whitespace(cstr[index_curr])
// 		&& cstr[index_curr] != '<'
// 		&& cstr[index_curr] != '>'
// 		&& cstr[index_curr] != '|'
// 	) {
// 		if (cstr[index_curr] == '\'')
// 		{
// 			if (tokenise_quotation(cstr, redir, &index_curr, &index_prev, '\''))
// 				return (EXIT_FAILURE);
// 		}
//
// 		else if (cstr[index_curr] == '"')
// 		{
// 			if (tokenise_quotation(cstr, redir, &index_curr, &index_prev, '"'))
// 				return (EXIT_FAILURE);
// 		}
//
// 		else
// 			index_curr++;
// 	}
//
// 	// adds any trailing input at the end of the redirection (ex: 'tes't)
// 	if (index_prev != index_curr)
// 	{
// 		arr_str_append(redir, NULL);
// 		str_append_range(redir->last, cstr, index_prev, index_curr);
// 	}
//
// 	if (len_prev == redir->len)
// 	{
// 		printf(ERR_REDIR, index_prev);
// 		return (EXIT_FAILURE);
// 	}
//
// 	arr_str_append(redir, NULL);
// 	str_append(redir->last, WHITESPACE);
// 	
// 	while (is_whitespace(cstr[index_curr]))
// 		index_curr++;
// 	index_prev = index_curr;
// 	
// 	*ptr_prev = index_prev;
// 	*ptr_curr = index_curr;
//
// 	return (EXIT_SUCCESS);
// }
//
// static uint8_t	tokenise_pipe(
// 	char *_Nonnull cstr,
// 	t_arr_str *_Nonnull arg,
// 	t_arr_str *_Nonnull redir,
// 	size_t *_Nonnull ptr_curr,
// 	size_t *_Nonnull ptr_prev
// ) {
// 	size_t	index_curr;
// 	
// 	if (
// 		cstr == NULL
// 		|| arg == NULL
// 		|| redir == NULL
// 		|| ptr_curr == NULL
// 		|| ptr_prev == NULL
// 	) {
// 		return (fail_at("tokenise_pipe", EINVAL));
// 	}
//
// 	arr_str_append(arg, NULL);
// 	str_append(arg->last, PIPE);
// 	arr_str_append(redir, NULL);
// 	str_append(redir->last, PIPE);
//
// 	index_curr = *ptr_curr + 1;
// 	while (is_whitespace(cstr[index_curr]))
// 		index_curr++;
//
// 	*ptr_prev = index_curr;
// 	*ptr_curr = index_curr;
//
// 	return (EXIT_SUCCESS);
// }
//
// static uint8_t	save_prev(
// 	char *_Nonnull cstr,
// 	t_arr_str *_Nonnull dst,
// 	size_t *_Nonnull ptr_curr,
// 	size_t *_Nonnull ptr_prev
// ) {
// 	size_t	index_prev;
// 	size_t	index_curr;
//
// 	if (cstr == NULL || dst == NULL || ptr_curr == NULL || ptr_prev == NULL)
// 		return (fail_at("save_prev", EINVAL));
//
// 	index_prev = *ptr_prev;
// 	index_curr = *ptr_curr;
//
// 	if (index_prev != index_curr)
// 	{
// 		arr_str_append(dst, NULL);
// 		str_append_range(dst->last, cstr, index_prev, index_curr);
// 	}
// 	
// 	*ptr_prev = *ptr_curr;
// 	return (EXIT_SUCCESS);
// }

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
	while (is_whitespace(str.get[i_curr]))
		i_prev++;

	i_curr = i_prev;
	while (str.get[i_curr] != '\0')
	{
		if (str.get[i_curr] == '\'')
		{
			// if (save_prev(str, arg, &i_curr, &i_prev))
			// 	return (EXIT_FAILURE);
			if (tokenise_quotation(str, arg, &i_curr, &i_prev, '\''))
				return (EXIT_FAILURE);
		}

		else if (str.get[i_curr] == '"')
		{
			// if (save_prev(str, arg, &i_curr, &i_prev))
			// 	return (EXIT_FAILURE);
			if (tokenise_quotation(str, arg, &i_curr, &i_prev, '"'))
				return (EXIT_FAILURE);
		}
		
		// else if (is_whitespace(str[index_curr]))
		// {
		// 	if (save_prev(str, arg, &index_curr, &index_prev))
		// 		return (EXIT_FAILURE);
		// 	if (tokenise_whitespace(str, arg, &index_curr, &index_prev))	
		// 		return (EXIT_FAILURE);
		// }
		//
		// else if (str[index_curr] == '<' || str[index_curr] == '>')
		// {
		// 	if (save_prev(str, arg, &index_curr, &index_prev))
		// 		return (EXIT_FAILURE);
		// 	if (tokenise_redir(str, redir, &index_curr, &index_prev))
		// 		return (EXIT_FAILURE);
		// }
		//
		// else if (str[index_curr] == '|')
		// {
		// 	if (save_prev(str, arg, &index_curr, &index_prev))
		// 		return (EXIT_FAILURE);
		// 	if (tokenise_pipe(str, arg, redir, &index_curr, &index_prev))
		// 		return (EXIT_FAILURE);
		// }

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

