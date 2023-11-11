/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:43:44 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 17:40:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_cleanup.h"

#include <stdbool.h>
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

	vstr_destroy(data->arg);
	vstr_destroy(data->redir);
	vcmd_destroy(data->cmd);

	data->arg = NULL;
	data->redir = NULL;
	data->cmd = NULL;
	data->exit_code = EXIT_SUCCESS;

	return (EXIT_SUCCESS);
}
