/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:38:46 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:31:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_destroy.h"

#include <stddef.h>

#include "dynamic/vector.h"
#include "env_pair_destroy.h"

void	env_destroy(t_vptr *_Nullable env)
{
	size_t		index;

	if (env == NULL)
		return ;
	index = 0;
	while (index < env->len)
	{
		env_pair_destroy(vptr_get_ptr(t_env_pair, env, index));
		index++;
	}
	vptr_destroy(env);
}
