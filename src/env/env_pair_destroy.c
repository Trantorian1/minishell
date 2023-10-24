/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pair_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:02:59 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 17:04:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_pair_destroy.h"

#include "dynamic/string.h"

void	env_pair_destroy(t_env_pair *env_pair)
{
	if (env_pair == NULL)
		return ;

	str_destroy(&env_pair->key);
	str_destroy(&env_pair->val);
}
