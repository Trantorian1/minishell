/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:25:12 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 04:05:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_EXEC_PATH_H
# define GET_EXEC_PATH_H

# include "dynamic/string.h"
# include "s_data.h"

t_str	get_exec_path(t_vptr *_Nonnull env, t_cstr _Nonnull exec);

#endif
