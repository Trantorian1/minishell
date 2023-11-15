/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:59:19 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:44:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdout_read.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "dynamic/string.h"

#define BUFFER_SIZE	1024

uint8_t	stdout_read(t_str *_Nonnull str, int32_t fd)
{
	ssize_t	n;
	char	buffer[BUFFER_SIZE];

	if (str == NULL || fd < 1)
		return (EXIT_FAILURE);
	n = BUFFER_SIZE - 1;
	while (n == BUFFER_SIZE - 1)
	{
		n = read(fd, buffer, BUFFER_SIZE - 1);
		if (n == -1)
			return (EXIT_FAILURE);
		buffer[n] = '\0';
		str_append_str(str, buffer);
	}
	return (EXIT_SUCCESS);
}
