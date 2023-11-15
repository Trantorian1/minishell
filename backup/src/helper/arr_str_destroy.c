/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_str_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:17:52 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:34:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr_str_destroy.h"

#include <stddef.h>

#include "dynamic/alloc.h"

void	arr_str_destroy(t_cstr _Nonnull *_Nullable arr)
{
	size_t	index;

	if (arr == NULL)
		return ;
	index = 0;
	while (arr[index] != NULL)
	{
		safe_free(arr[index]);
		index++;
	}
	safe_free(arr);
}
