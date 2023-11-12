/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_collect.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:43:50 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 12:58:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_COLLECT_H
# define ENV_COLLECT_H

# include "dynamic/vector.h"
# include "dynamic/string.h"

t_cstr _Nonnull *_Nullable	env_collect(t_vptr *_Nonnull env);

#endif
