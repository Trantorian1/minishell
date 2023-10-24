/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:25:08 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 17:28:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UPDATE_H
# define ENV_UPDATE_H

# include "dynamic/vector.h"
# include "s_env.h"

t_vptr *_Nullable	env_update(t_vptr *_Nonnull env, t_cstr _Nonnull pair);

#endif
