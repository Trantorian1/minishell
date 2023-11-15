/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_get.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:47:33 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 18:31:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_GET_H
# define BUILTIN_GET_H

# include "dynamic/string.h"
# include "e_builtin.h"

t_builtin	builtin_get(t_cstr _Nonnull cmd);

#endif
