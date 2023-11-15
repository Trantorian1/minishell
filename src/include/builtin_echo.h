/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:31:21 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:08:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ECHO_H
# define BUILTIN_ECHO_H

# include <stdint.h>
# include <stdbool.h>
# include "s_data.h"
# include "s_cmd.h"

uint8_t	builtin_echo(t_data *_Nonnull data, t_cmd cmd,
			int32_t *_Nonnull pipe_fd, bool in_child);

#endif
