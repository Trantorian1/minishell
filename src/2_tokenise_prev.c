/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenise_prev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 06:58:28 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:46:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenise_prev.h"

#include <stdlib.h>

uint8_t	tokenise_prev(
	t_vptr *_Nonnull vptr,
	t_str input,
	size_t i_prev,
	size_t i_curr
) {
	if (vptr == NULL)
		return (EXIT_FAILURE);
	if (i_prev != i_curr)
		vstr_append(vptr, str_substr(input, i_prev, i_curr));
	return (EXIT_SUCCESS);
}
