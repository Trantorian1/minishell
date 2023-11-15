/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:54:51 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:14:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_H
# define BUILTIN_ENV_H

# include <stdint.h>
# include <stdbool.h>
# include "s_data.h"
# include "s_cmd.h"

uint8_t	builtin_env(t_data *_Nonnull data, t_cmd cmd, int32_t *_Nonnull pipe_fd,
			bool in_child);

#endif
