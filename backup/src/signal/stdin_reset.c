/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:26:45 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:44:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdin_reset.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int32_t	stdin_reset(int32_t fd_old, int32_t fd_new)
{
	if (fd_old < 1 || fd_new < 1)
		return (EXIT_FAILURE);
	close(fd_new);
	if (dup2(fd_old, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
