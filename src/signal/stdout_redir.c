/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:11:10 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:44:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdout_redir.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "dynamic/string.h"

uint8_t	stdout_redir(int32_t *_Nonnull fd_old, int32_t *_Nonnull fd_new)
{
	int32_t	pipe_id[2];
	int32_t	flags;

	if (fd_old == NULL || fd_new == NULL || pipe(pipe_id) == -1)
		return (EXIT_FAILURE);
	*fd_old = dup(STDOUT_FILENO);
	if (*fd_old == -1)
		return (EXIT_FAILURE);
	if (dup2(pipe_id[1], STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	*fd_new = pipe_id[0];
	close(pipe_id[1]);
	flags = fcntl(*fd_new, F_GETFL, 0);
	if (flags == -1)
		return (EXIT_FAILURE);
	flags |= O_NONBLOCK;
	if (fcntl(*fd_new, F_SETFL, flags) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
