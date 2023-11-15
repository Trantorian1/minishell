/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:50:41 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:06:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_PWD_H
# define BUILTIN_PWD_H

# include <stdint.h>
# include "s_data.h"
# include "s_cmd.h"

uint8_t	builtin_pwd(t_data *_Nonnull data, t_cmd cmd, int32_t *_Nonnull pipe_fd,
			bool in_child);

#endif
