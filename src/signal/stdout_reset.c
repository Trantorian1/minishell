/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:10:21 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 12:51:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdout_reset.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Restores STDOUT to its default fd.
 *
 * @param fd_old (int32_t): old STDOUT fd.
 * @param fd_new (int32_t): new STDOUT fd, redirected and used for testing.
 *
 * @return (uint8_t): EXIT_SUCCESS if no error occurs, EXIT_FAILURE otherwise.
 */
uint8_t	stdout_reset(int32_t fd_old, int32_t fd_new)
{
	if (fd_old < 1 || fd_new < 1)
		return (EXIT_FAILURE);

	close(fd_new);
	if (dup2(fd_old, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	close(fd_old);

	return (EXIT_SUCCESS);
}
