/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:40:40 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:42:31 by marvin           ###   ########.fr       */
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

	fd = dup2(oldfd, newfd);
	if (fd != -1)
		return (fd);
	safe_exit(EXIT_FAILURE);
}
