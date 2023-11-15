/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_try_delete.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:32:44 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:09:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TRY_DELETE_H
# define ENV_TRY_DELETE_H

# include <stdint.h>
# include "dynamic/vector.h"
# include "dynamic/string.h"
# include "s_env.h"

uint8_t	env_try_delete(t_vptr *_Nonnull env, t_cstr _Nonnull key);

#endif
