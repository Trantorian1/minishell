/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:29:45 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdint.h>

# include "e_builtin.h"
# include "s_cmd.h"
# include "s_data.h"

typedef uint8_t	(*f_builtin)(t_data *_Nonnull data, t_cmd cmd, int32_t *_Nonnull pipe_fd);

uint8_t	builtin(t_data *_Nonnull data, t_cmd cmd, t_builtin type, int32_t *_Nonnull pipe_fd);

#endif
