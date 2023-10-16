/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:59:19 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 14:49:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdout_read.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "dynamic/string.h"

#define BUFFER_SIZE	1024

/**
 * @brief Reads ouput from stdout and saves it to a string.
 *
 * @param str (t_str *_Nonnull): string to save output in.
 * @param fd (int32_t): fd to read from.
 *
 * @return (uint8_t): EXIT_SUCCESS if no error occurs, EXIT_FAILURE otherwise.
 * This is the case if the program cannot read from STDOUT for example (no
 * output sent).
 */
uint8_t	stdout_read(t_str *_Nonnull str, int32_t fd)
{
	ssize_t	n;
	char	buffer[BUFFER_SIZE];

	if (str == NULL || fd < 1)
		return (EXIT_FAILURE);
	
	// while not all output has been captured...
	n = BUFFER_SIZE - 1;
	while (n == BUFFER_SIZE - 1)
	{
		// ...read from fd
		n = read(fd, buffer, BUFFER_SIZE - 1);
		if (n == -1)
			return (EXIT_FAILURE);
		buffer[n] = '\0';
		// ...and appends contents to string
		str_append(str, buffer);
	}

	return (EXIT_SUCCESS);
}
