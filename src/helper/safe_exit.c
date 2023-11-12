/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:51:57 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 13:58:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_exit.h"

#include <readline/readline.h>
#include <stdlib.h>

#include "dynamic/alloc.h"

_Noreturn void	safe_exit(uint8_t error)
{
	safe_free_all();
	rl_clear_history();
	exit(error);
}
