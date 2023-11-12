/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_collect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:45:45 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 12:58:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_collect.h"

#include <stddef.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "dynamic/alloc.h"
#include "dynamic/memory.h"
#include "s_env.h"

t_cstr _Nonnull *_Nullable	env_collect(t_vptr *_Nonnull env)
{
	t_cstr		*cenv;
	size_t		index;
	t_env_pair	pair;

	if (env == NULL)
		return (NULL);

	cenv = safe_alloc(sizeof(*cenv) * (env->len + 1));
	cenv[env->len] = NULL;

	index = 0;
	while (index < env->len)
	{
		pair = vptr_get(t_env_pair, env, index);
		cenv[index] = cstr_alloc(pair.key.len + pair.val.len + 1);
		
		dyn_memcpy(cenv[index], pair.key.get, pair.key.len);
		dyn_memcpy(cenv[index] + pair.key.len, "=", 1);
		dyn_memcpy(cenv[index] + pair.key.len + 1, pair.val.get, pair.val.len);

		index++;
	}

	return (cenv);
}
