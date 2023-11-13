/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_try_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:34:35 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 23:27:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_try_delete.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "env_pair_destroy.h"

uint8_t	env_try_delete(t_vptr *_Nonnull env, t_cstr _Nonnull key)
{
	size_t		index;
	t_env_pair	pair;

	if (env == NULL || key == NULL)
		return (false);

	index = 0;
	while (index < env->len)
	{
		pair = vptr_get(t_env_pair, env, index);

		if (str_eq(pair.key, key))
		{
			vptr_rm(env, index);
			env_pair_destroy(&pair);
			return (true);
		}

		index++;
	}

	return (false);
}
