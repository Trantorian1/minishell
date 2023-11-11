/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:33:51 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 18:44:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_echo.h"

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>

#include "dynamic/string.h"

uint8_t	builtin_echo(t_data *_Nonnull data, t_cmd cmd)
{
	uint8_t	option_n;
	size_t	index;
	size_t	len;

	if (data == NULL)
		return (EXIT_FAILURE);

	if (cstr_eq(cmd.arg[1], "-n"))
		option_n = true;
	else
		option_n = false;

	index = 1 + option_n;

	while (cmd.arg[index] != NULL)
	{
		len = cstr_len(cmd.arg[index]);
		write(STDOUT_FILENO, cmd.arg[index], len);
		
		if (cmd.arg[index + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);

		index++;
	}
	if (option_n == false)
		write(STDOUT_FILENO, "\n", 1);

	return (EXIT_SUCCESS);
}
