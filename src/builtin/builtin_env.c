/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:56:11 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 20:09:33 by marvin           ###   ########.fr       */
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
#include "s_env.h"

uint8_t	builtin_env(t_data *_Nonnull data, t_cmd cmd)
{
	size_t		index;
	t_env_pair	pair;

	if (data == NULL)
		return (EXIT_FAILURE);

	if (cmd.arg[1] != NULL)
		write(STDERR_FILENO, "minishell: env: too many arguments\n", 35);

	index = 0;
	while (index < data->env->len)
	{
		pair = vptr_get(t_env_pair, data->env, index);

		write(STDOUT_FILENO, pair.key.get, pair.key.len);
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, pair.val.get, pair.val.len);
		write(STDOUT_FILENO, "\n", 1);

		index++;
	}

	return (EXIT_SUCCESS);
}
