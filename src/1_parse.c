/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:28:08 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:45:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_parse.h"

#include <readline/readline.h>
#include <stdlib.h>
#include <stdint.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "input_get.h"

#include "s_data.h"
#include "d_str.h"

uint8_t	state_parse(t_data *_Nonnull data)
{
	t_vptr	*user_input;

	if (data == NULL)
		return (EXIT_FAILURE);
	user_input = input_get(PROMPT_DEFAULT);
	if (user_input == NULL)
		return (EXIT_FAILURE);
	data->user_input = user_input;
	data->index_line = 0;
	return (EXIT_SUCCESS);
}
