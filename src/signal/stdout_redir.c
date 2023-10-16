/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:11:10 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 15:07:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdout_redir.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "dynamic/string.h"

/**
 * @brief Redirects STDOUT to a new non-blocking fd which can be used to observe
 * program output. 
 *
 * Note that this means that any call to functions that read STDOUT will not
 * wait for imput, such as in the case of read(3).
 *
 * @param fd_old (int32_t *_Nonnull): will be set to contain old STDOUT fd.
 * @param fd_new (int32_t *_Nonnull): will be set to contain new STDOUT fd.
 *
 * @return (uint8_t): EXIT_SUCCESS if no error occurs, EXIT_FAILURE otherwise.
 */
uint8_t	stdout_redir(int32_t *_Nonnull fd_old, int32_t *_Nonnull fd_new)
{
	int32_t	pipe_id[2];
	int32_t	flags;

	if (fd_old == NULL || fd_new == NULL || pipe(pipe_id) == -1)
		return (EXIT_FAILURE);

	// makes a copy of STDOUT
	*fd_old = dup(STDOUT_FILENO);
	if (*fd_old == -1)
		return (EXIT_FAILURE);

	// redirects STDOUT
	if (dup2(pipe_id[1], STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	*fd_new = pipe_id[0];
	close(pipe_id[1]);

	// gets the current flags on fd_new
	flags = fcntl(*fd_new, F_GETFL, 0);
	if (flags == -1)
		return (EXIT_FAILURE);

	// makes fd_new non-blocking
	flags |= O_NONBLOCK;
	if (fcntl(*fd_new, F_SETFL, flags) == -1)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
