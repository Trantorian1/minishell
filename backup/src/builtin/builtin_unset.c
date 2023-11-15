/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:29:45 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:30:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_unset.h"

#include <stddef.h>
#include <stdlib.h>

#include "env_try_delete.h"

uint8_t	builtin_unset(
	t_data *_Nonnull data,
	t_cmd cmd,
	int32_t *_Nonnull pipe_fd,
	bool in_child
) {
	size_t	index;

	(void)pipe_fd;
	(void)in_child;
	if (data == NULL)
		return (EXIT_FAILURE);
	index = 1;
	while (cmd.arg[index] != NULL)
	{
		env_try_delete(data->env, cmd.arg[index]);
		index++;
	}
	return (EXIT_FAILURE);
}
