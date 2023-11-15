/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:56:15 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 18:25:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_get.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "error_display.h"

static inline bool	no_fuckery(t_cstr _Nullable input);

t_vptr *_Nullable	input_get(char *_Nonnull prompt)
{
	t_cstr	tmp;
	t_str	input;
	t_vptr	*line_arr;

	if (prompt == NULL)
		return (NULL);
	tmp = readline(prompt);
	if (no_fuckery(tmp) && *prompt != '>')
		add_history(tmp);
	else
		return (NULL);
	input = str_create(tmp);
	line_arr = str_split(input, "\n");
	free(tmp);
	str_destroy(&input);
	return (line_arr);
}

static inline bool	no_fuckery(t_cstr _Nullable input)
{
	size_t	index;

	if (input == NULL)
		return (false);
	index = 0;
	while (input[index] != '\0' && input[index] >= 0)
		index++;
	if (input[index] != '\0')
	{
		error_display("input", "no hexadecimal fuckery allowed");
		return (false);
	}
	else
		return (true);
}
