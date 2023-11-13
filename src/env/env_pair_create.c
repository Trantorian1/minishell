/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pair_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:00:56 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 22:47:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_pair_create.h"

#include <stddef.h>
#include <stdbool.h>

#include "dynamic/character.h"
#include "dynamic/string.h"
#include "env_pair_destroy.h"

static inline bool	validate(t_str key);

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
	if (validate(env_pair.key) == false)
	{
		str_rm(&env_pair.key, 0, env_pair.key.len);
		str_rm(&env_pair.val, 0, env_pair.val.len);
	}

	return (env_pair);
}

static inline bool	validate(t_str key)
{
	size_t	index;
	int8_t	c;

	if (!is_letter(key.get[0]) && key.get[0] != '_')
		return (false);

	index = 1;
	while (index < key.len)
	{
		c = key.get[index];
		if (!is_letter(c) && !is_digit(c) && c != '_')
			return (false);
		index++;
	}

	return (true);
}
