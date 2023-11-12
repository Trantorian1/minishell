/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:43:24 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 16:14:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_close.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "dynamic/alloc.h"
#include "safe_exit.h"

int32_t	safe_close(int32_t fd)
{
	if (close(fd) == 0)
		return (EXIT_SUCCESS);

	perror("minishell: close");
	safe_exit(EXIT_FAILURE);
}
