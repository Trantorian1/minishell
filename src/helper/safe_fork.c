/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:14:27 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:42:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_fork.h"

#include <unistd.h>
#include <stdlib.h>

#include "dynamic/alloc.h"
#include "safe_exit.h"

pid_t	safe_fork(void)
{
	pid_t	fid;

	fid = fork();
	if (fid == -1)
	{
		safe_free_all();
		safe_exit(EXIT_FAILURE);
	}
	return (fid);
}
