/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pair_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:00:56 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 17:18:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_pair_create.h"

t_env_pair	env_pair_create(t_cstr _Nonnull pair)
{
	t_env_pair	env_pair;
	t_str		src;
	size_t		match;

	if (pair == NULL)
		return ((t_env_pair){ {0}, {0} });

	src = str_create(pair);
	match = str_find_char(src, '=');
	
	if (match == src.len)
	{
		str_destroy(&src);
		return ((t_env_pair){ {0}, {0} });
	}

	env_pair.key = str_substr(src, 0, match);
	env_pair.val = str_substr(src, match + 1, src.len);
	str_destroy(&src);

	return (env_pair);
}
