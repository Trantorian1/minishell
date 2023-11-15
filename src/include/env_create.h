/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:54:54 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 16:57:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_CREATE_H
# define ENV_CREATE_H

# include "dynamic/vector.h"
# include "dynamic/string.h"
# include "s_env.h"

t_vptr *_Nullable	env_create(t_cstr _Nonnull *_Nonnull env);

#endif
