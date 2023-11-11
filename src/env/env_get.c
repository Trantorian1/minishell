/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:20:45 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 20:20:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_get.h"

#include <stddef.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "s_env.h"

t_str	env_get(t_vptr *_Nonnull env, t_cstr _Nonnull key)
{
	size_t		index;
	t_env_pair	pair;

	if (env == NULL || key == NULL)
		return ((t_str){ 0, "", 0 });

	index = 0;
	while (index < env->len)
	{
		pair = vptr_get(t_env_pair, env, index);
		if (str_eq(pair.key, key))
			return (pair.val);

		index++;
	}

	return ((t_str){ 0, "", 0 });
}
