/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:52:23 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 12:02:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ENV_H
# define S_ENV_H

# include <stddef.h>
# include <stdint.h>
# include "dynamic/string.h"

typedef struct s_env_pair
{
	t_str	key;
	t_str	val;
}	t_env_pair;

#endif
