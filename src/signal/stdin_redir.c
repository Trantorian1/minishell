/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:44:20 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:44:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdin_redir.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

uint8_t	stdin_redir(int32_t *_Nonnull fd_old, int32_t *_Nonnull fd_new)
{
	int32_t	pipe_fd[2];

	if (fd_old == NULL || fd_new == NULL || pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	*fd_new = pipe_fd[1];
	*fd_old = dup(STDIN_FILENO);
	if (*fd_old == -1)
		return (EXIT_FAILURE);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	close(pipe_fd[0]);
	return (EXIT_SUCCESS);
}
