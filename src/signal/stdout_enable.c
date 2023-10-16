/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_enable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:07:56 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 14:09:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdout_enable.h"

#include <stdint.h>
#include <unistd.h>

int32_t	stdout_enable(int32_t fd_old)
{
	return (dup2(fd_old, STDOUT_FILENO));
}
