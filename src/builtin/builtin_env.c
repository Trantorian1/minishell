/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:56:11 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 21:34:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_env.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "dynamic/string.h"
#include "dynamic/vector.h"
#include "error_display.h"

#include "s_env.h"
#include "d_pipe.h"
#include "safe_close.h"

uint8_t	builtin_env(t_data *_Nonnull data, t_cmd cmd, int32_t *_Nonnull pipe_fd)
{
	size_t		index;
	t_env_pair	pair;
	t_str		message;

	if (data == NULL || pipe_fd == NULL)
		return (EXIT_FAILURE);

	if (cmd.arg[1] != NULL)
		error_display("env", "too many arguments");

	index = 0;
	while (index < data->env->len)
	{
		pair = vptr_get(t_env_pair, data->env, index);
		message = str_create(pair.key.get);

		str_append_char(&message, '=');
		str_append_str(&message, pair.val.get);
		str_append_char(&message, '\n');
		write(pipe_fd[PIPE_WRITE], message.get, message.len);
		str_destroy(&message);

		index++;
	}

	return (EXIT_SUCCESS);
}
