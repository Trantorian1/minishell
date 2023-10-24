/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:19:36 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 17:23:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_GET_H
# define ENV_GET_H

# include "dynamic/vector.h"
# include "dynamic/string.h"

t_str	env_get(t_vptr *_Nonnull env, t_cstr _Nonnull key);

#endif
