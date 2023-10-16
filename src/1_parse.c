/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:28:08 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 12:37:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_parse.h"

#include <readline/readline.h>
#include <stdlib.h>
#include <stdint.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"

#include "s_data.h"
#include "d_str.h"

static t_vptr *_Nullable	parse(char *_Nonnull prompt);

uint8_t	state_parse(t_data *_Nonnull data)
{
	t_vptr	*user_input;

	if (data == NULL)
		return (EXIT_FAILURE);

	user_input = parse(PROMPT_DEFAULT);
	if (user_input == NULL)
		return (EXIT_FAILURE);

	data->user_input = user_input;
	data->index_line = 0;

	return (EXIT_SUCCESS);
}

static t_vptr *_Nullable	parse(char *_Nonnull prompt)
{
	t_cstr	tmp;
	t_str	input;
	t_vptr	*line_arr;

	// checks for invalid parameters
	if (prompt == NULL)
		return (NULL);

	// user input is split at every newline
	tmp = readline(prompt);
	if (tmp == NULL)
		return (NULL);

	input = str_create(tmp);
	line_arr = str_split(input, "\n");

	// frees up unnecessary variables
	free(tmp);
	str_destroy(&input);

	return (line_arr);
}

