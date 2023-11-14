/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 07:45:18 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 07:45:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skip_whitespace.h"

#include "dynamic/character.h"

size_t	skip_whitespace(t_str str, size_t i_curr)
{
	if (str.len <= i_curr)
		return (str.len);

	while (str.get[i_curr] != '\0' && is_whitespace(str.get[i_curr]))
		i_curr++;

	return (i_curr);
}
