/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:43:24 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 16:44:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_close.h"

#include <unistd.h>
#include <stdlib.h>

#include "dynamic/alloc.h"

int32_t	safe_close(int32_t fd)
{
	int32_t	error;

	error = close(fd);
	if (error == 0)
		return (EXIT_SUCCESS);

	safe_free_all();
	exit(EXIT_FAILURE);
}
