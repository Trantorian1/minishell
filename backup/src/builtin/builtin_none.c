/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_none.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:42:27 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:30:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_none.h"

#include <stdlib.h>

uint8_t	builtin_none(
	t_data *_Nonnull data,
	t_cmd cmd,
	int32_t *_Nonnull pipe_fd,
	bool in_child
) {
	(void)cmd;
	(void)pipe_fd;
	(void)in_child;
	if (data == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
