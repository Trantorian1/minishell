/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_send.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:09:58 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 14:21:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdin_send.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "dynamic/string.h"

uint32_t	stdin_send(char *_Nonnull cstr, int32_t fd)
{
	if (cstr == NULL || fd < 1)
		return (EXIT_FAILURE);

	if (write(fd, cstr, cstr_len(cstr)) == -1)
		return (EXIT_FAILURE);
	if (write(fd, "\n", 1) == -1)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
