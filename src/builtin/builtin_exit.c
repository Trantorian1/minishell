/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:10:37 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 18:29:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_exit.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "dynamic/vector.h"
#include "state_cleanup.h"
#include "env_destroy.h"

uint8_t	builtin_exit(t_data *_Nonnull data)
{
	if (data == NULL)
		return (EXIT_FAILURE);
	
	data->should_exit = true;
	state_cleanup(data);
	vstr_destroy(data->user_input);
	env_destroy(data->env);
	rl_clear_history();

	exit(EXIT_SUCCESS);
}
