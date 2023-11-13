/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:27:16 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 22:33:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_update.h"

#include "dynamic/character.h"
#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "env_pair_create.h"
#include "env_pair_destroy.h"

#include "error_display.h"
#include "s_env.h"
#include <stdio.h>

t_vptr *_Nullable	env_update(t_vptr *_Nonnull env, t_cstr _Nonnull cstr)
{
	t_env_pair	pair_new;
	t_env_pair	*pair_curr;
	size_t		index;

	if (env == NULL || cstr == NULL)
		return (NULL);

	pair_new = env_pair_create(cstr);
	if (pair_new.key.len == 0)
	{
		error_display("export", "invalid identifier");
		env_pair_destroy(&pair_new);
		return (NULL);
	}

	index = 0;
	while (index < env->len)
	{
		pair_curr = vptr_get_ptr(t_env_pair, env, index);
		if (str_eq(pair_curr->key, pair_new.key.get))
		{
			str_rm(&pair_curr->val, 0, pair_curr->val.len);
			str_append_str(&pair_curr->val, pair_new.val.get);
			env_pair_destroy(&pair_new);
			return (env);
		}
		index++;
	}

	return (vptr_append(env, &pair_new));
}
