/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:36:36 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 13:59:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_pipe.h"

#include <unistd.h>
#include <stdlib.h>

#include "dynamic/alloc.h"
#include "safe_exit.h"

int32_t	safe_pipe(int32_t pipefd[2])
{
	int32_t	error;

	error = pipe(pipefd);
	if (error == 0)
		return (0);
	
	safe_free_all();
	safe_exit(EXIT_FAILURE);
}
