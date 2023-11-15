/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_disable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:33:05 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:44:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdout_disable.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

int32_t	stdout_disable(void)
{
	int32_t	fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	if (fd_stdout == -1)
		return (-1);
	if (dup2(0, STDOUT_FILENO) == -1)
		return (-1);
	return (fd_stdout);
}
