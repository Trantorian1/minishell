/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:57:06 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 15:07:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_create.h"

#include <stddef.h>

#include "dynamic/vector.h"
#include "env_pair_create.h"

t_vptr *_Nullable	env_create(t_cstr _Nonnull *_Nonnull cstr_env)
{
	t_vptr		*env;
	t_env_pair	pair;
	size_t		index;

	if (cstr_env == NULL || *cstr_env == NULL)
		return (NULL);
	env = vptr_create(sizeof(t_env_pair), 0);
	index = 0;
	while (cstr_env[index] != NULL)
	{
		pair = env_pair_create(cstr_env[index]);
		vptr_append(env, &pair);
		index++;
	}
	return (env);
}
