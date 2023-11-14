/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:15:42 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 04:29:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_dup.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "safe_exit.h"

int32_t	safe_dup(int32_t fd)
{
	int32_t	fd_new;

	fd_new = dup(fd);
	if (fd_new < 0)
	{
		perror("dup");
		safe_exit(EXIT_FAILURE);
	}

	return (fd_new);
}
