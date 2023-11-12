/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:56:15 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 22:21:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_get.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"

t_vptr *_Nullable	input_get(char *_Nonnull prompt)
{
	t_cstr	tmp;
	t_str	input;
	t_vptr	*line_arr;

	// checks for invalid parameters
	if (prompt == NULL)
		return (NULL);

	// user input is split at every newline
	tmp = readline(prompt);
	if (*prompt != '>')
		add_history(tmp);
	if (tmp == NULL)
		return (NULL);

	input = str_create(tmp);
	line_arr = str_split(input, "\n");

	// frees up unnecessary variables
	free(tmp);
	str_destroy(&input);

	return (line_arr);
}

