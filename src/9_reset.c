/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_reset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:52:56 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:53:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_reset.h"

#include "dynamic/vector.h"

void	state_reset(t_data *_Nonnull data)
{
	if (data == NULL)
		return ;

	vstr_destroy(data->user_input);
	data->user_input = NULL;
	data->index_line = 0;
}
