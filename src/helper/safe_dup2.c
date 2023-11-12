/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:40:40 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 21:02:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_dup2.h"

#include <unistd.h>
#include <stdlib.h>

#include "dynamic/alloc.h"
#include "safe_exit.h"

int32_t	safe_dup2(int32_t oldfd, int32_t newfd)
{
	int32_t	fd;
	if (oldfd == newfd)
		return (EXIT_SUCCESS);

	fd = dup2(oldfd, newfd);
	if (fd != -1)
		return (fd);

	safe_exit(EXIT_FAILURE);
}
