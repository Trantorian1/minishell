/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:06:53 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 19:07:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_get.h"
#include <stdlib.h>

t_data *_Nonnull	data_get(void)
{
	static t_data	data = {
		.exit_code = EXIT_SUCCESS,
		.should_exit = false,
		.index_line = 0,
		.user_input = NULL,
		.arg = NULL,
		.redir = NULL,
	};

	return (&data);
}
