/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:10:21 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:45:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdout_reset.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

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
