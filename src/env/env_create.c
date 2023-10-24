/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:57:06 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 17:18:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_create.h"

#include <stddef.h>

#include "dynamic/vector.h"
#include "env_pair_create.h"

t_vptr *_Nullable	env_create(t_cstr _Nonnull *_Nonnull env)
{
	t_vptr		*venv;
	t_env_pair	pair;
	size_t		index;

	if (env == NULL || *env == NULL)
		return (NULL);

	venv = vptr_create(t_env_pair, 0);
	index = 0;

	while (env[index] != NULL)
	{
		pair = env_pair_create(env[index]);
		vptr_append(venv, &pair);
		index++;
	}

	return (venv);
}
