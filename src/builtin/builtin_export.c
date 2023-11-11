/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:01:05 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 19:53:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_export.h"

#include <stdint.h>
#include <stdlib.h>
#include "env_update.h"

uint8_t	builtin_export(t_data *_Nonnull data, t_cmd cmd)
{
	size_t	index;

	if (data == NULL)
		return (EXIT_FAILURE);

	index = 1;
	if (cmd.arg[1] == NULL)
		// TODO: implement env
		return (EXIT_SUCCESS);
		
	while (cmd.arg[index] != NULL)
	{
		env_update(data->env, cmd.arg[index]);
		index++;
	}

	return (EXIT_FAILURE);
}
