/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_none.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:42:27 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_none.h"

#include <stdlib.h>

uint8_t	builtin_none(t_data *_Nonnull data, t_cmd cmd, int32_t *_Nonnull pipe_fd)
{
	if (data == NULL)
		return (EXIT_FAILURE);

	(void)cmd;
	(void)pipe_fd;

	return (EXIT_SUCCESS);
}
