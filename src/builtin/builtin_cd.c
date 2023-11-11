/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:51:57 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 18:58:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd.h"

#include <stdlib.h>
#include <stddef.h>

uint8_t	builtin_cd(t_data *_Nonnull data, t_cmd cmd)
{
	if (data == NULL || cmd.arg[0] == NULL)
		return (EXIT_FAILURE);

	if (cmd.arg[1] == NULL)
		return (EXIT_SUCCESS);
	if (cmd.arg[2] != NULL)
		return (EXIT_FAILURE);


	
	return (EXIT_SUCCESS);
}
