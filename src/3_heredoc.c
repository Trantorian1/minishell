/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:39:45 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_display.h"
#include "state_heredoc.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "dynamic/character.h"
#include "input_get.h"

#include "d_str.h"

static t_str	delimiter_get(t_vptr *_Nonnull redir, size_t i_curr);

static t_str	heredoc_content(
	t_data *_Nonnull data,
	t_vptr *_Nonnull redir,
	t_str delimiter,
	size_t i_curr
);

uint8_t	state_heredoc(t_data *_Nonnull data)
{
	size_t	index;
	t_str	redir_curr;
	t_str	delimiter;
	t_str	content;

	if (data == NULL)
		return (EXIT_FAILURE);

	index = 0;
	while (index < data->redir->len)
	{
		redir_curr = vptr_get(t_str, data->redir, index);

		if (str_eq(redir_curr, HEREDOC))
		{
			index++;
			delimiter = delimiter_get(data->redir, index);

			content = heredoc_content(data, data->redir, delimiter, index);
			vstr_insert(data->redir, content, index);
			str_destroy(&delimiter);

			index++;
		}
		index++;
	}

	return (EXIT_SUCCESS);
}

static t_str	delimiter_get(
	t_vptr *_Nonnull redir,
	size_t i_curr
) {
	t_str	str_curr;
	t_str	delimiter;

	if (redir == NULL || i_curr >= redir->len)
		return (str_create(""));

	str_curr = vptr_get(t_str, redir, i_curr);
	delimiter = str_create("");

	str_curr = vptr_get(t_str, redir, i_curr);
	while (!str_eq(str_curr, WHITESPACE))
	{
		if (!str_eq(str_curr, QUOTE_DOUBLE) && !str_eq(str_curr, QUOTE_SINGLE))
			str_append_str(&delimiter, str_curr.get);

		vstr_rm(redir, i_curr);
		str_curr = vptr_get(t_str, redir, i_curr);
	}

	return (delimiter);
}

static t_str	heredoc_content(
	t_data *_Nonnull data,
	t_vptr *_Nonnull redir,
	t_str delimiter,
	size_t i_curr
) {
	t_str	content;
	t_str	line;
	t_vptr	*input;

	if (redir == NULL || i_curr >= redir->len)
		return (str_create(""));

	content = str_create("");

	while(true)
	{
		if (data->index_line == data->user_input->len)
		{
			input = input_get("> ");
			if (input == NULL)
			{
				error_display("heredoc", "eof encountered");
				return (content);
			}
			if (input->len == 0)
			{
				str_append_char(&content, '\n');
				vptr_destroy(input);
				continue ;
			}
			vptr_join(data->user_input, input);
			vptr_destroy(input);
		}
		line = vptr_get(t_str, data->user_input, data->index_line);

		if (str_eq(line, delimiter.get))
		{
			vstr_rm(data->user_input, data->index_line);
			break ;
		}
		else
		{
			str_append_str(&content, line.get);
			str_append_char(&content, '\n');
			data->index_line++;
		}
	}

	return (content);
}
