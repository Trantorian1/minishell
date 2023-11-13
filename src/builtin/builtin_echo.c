/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:33:51 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_echo.h"

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

#include "dynamic/string.h"

#include "d_pipe.h"

uint8_t	builtin_echo(t_data *_Nonnull data, t_cmd cmd, int32_t * _Nonnull pipe_fd)
{
	uint8_t	option_n;
	size_t	index;
	t_str	message;

	if (data == NULL || pipe_fd == NULL)
		return (EXIT_FAILURE);

	if (cstr_eq(cmd.arg[1], "-n"))
		option_n = true;
	else
		option_n = false;

	index = 1 + option_n;
	message = str_create("");

	while (cmd.arg[index] != NULL)
	{
		str_append_str(&message, cmd.arg[index]);
		if (cmd.arg[index + 1] != NULL)
			str_append_char(&message, ' ');

		index++;
	}
	if (option_n == false)
		str_append_char(&message, '\n');

	write(pipe_fd[PIPE_WRITE], message.get, message.len);
	str_destroy(&message);

	return (EXIT_SUCCESS);
}
