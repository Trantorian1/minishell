/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:39:45 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 05:47:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_display.h"
#include "safe_close.h"
#include "safe_dup.h"
#include "safe_dup2.h"
#include "sig_heredoc.h"
#include "sig_main.h"
#include "sigtype.h"
#include "state_heredoc.h"

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "dynamic/character.h"
#include "input_get.h"
#include "delimiter_get.h"

#include "d_str.h"

static inline t_str	heredoc_content(
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
			index += 2;
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

static inline uint8_t	update_input(t_data *_Nonnull data)
{
	t_vptr	*input;
	
	input = input_get("> ");
	if (sigtype == SIGINT)
		return (EXIT_FAILURE);
	if (input == NULL)
	{
		error_display("heredoc", "eof encountered");
		return (EXIT_FAILURE);
	}
	if (input->len != 0)
		vptr_join(data->user_input, input);
	else
		vstr_append(data->user_input, str_create(""));
	vptr_destroy(input);
	return (EXIT_SUCCESS);
}

static inline uint8_t	update_content(
	t_data *_Nonnull data,
	t_str *_Nonnull content,
	t_str delimiter
) {
	t_str	line;

	line = vptr_get(t_str, data->user_input, data->index_line);

	if (str_eq(line, delimiter.get))
	{
		vstr_rm(data->user_input, data->index_line);
		return (EXIT_FAILURE);
	}
	else
	{
		str_append_str(content, line.get);
		str_append_char(content, '\n');
		data->index_line++;
	}

	return (EXIT_SUCCESS);
}

static inline void	heredoc_reset(int32_t stdin_prev)
{
	sig_main();
	if (sigtype == SIGINT)
	{
		safe_dup2(stdin_prev, STDIN_FILENO);
		write(STDIN_FILENO, "\n", 1);
	}
	safe_close(stdin_prev);
}

static inline t_str	heredoc_content(
	t_data *_Nonnull data,
	t_vptr *_Nonnull redir,
	t_str delimiter,
	size_t i_curr
) {
	t_str	content;
	int32_t	stdin_prev;

	if (redir == NULL || i_curr >= redir->len)
		return (str_create(""));

	content = str_create("");
	stdin_prev = dup(STDIN_FILENO);
	sig_heredoc();

	while(true)
	{
		if (data->index_line == data->user_input->len && update_input(data))
			break ;
		if (update_content(data, &content, delimiter))
			break ;
	}
	heredoc_reset(stdin_prev);

	return (content);
}
