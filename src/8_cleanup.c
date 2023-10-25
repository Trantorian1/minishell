/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:43:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 17:53:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_cleanup.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "env_destroy.h"
#include "vcmd_destroy.h"

uint8_t	state_cleanup(t_data *_Nonnull data)
{
	if (data == NULL)
		return (EXIT_FAILURE);

	vstr_destroy(data->user_input);
	vstr_destroy(data->arg);
	vstr_destroy(data->redir);
	env_destroy(data->env);
	vcmd_destroy(data->cmd);

	data->index_line = 0;
	data->user_input = NULL;
	data->arg = NULL;
	data->redir = NULL;
	data->env = NULL;
	data->cmd = NULL;
	data->exit = 0;

	return (EXIT_SUCCESS);
}
