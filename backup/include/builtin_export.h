/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:58:18 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:07:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_EXPORT_H
# define BUILTIN_EXPORT_H

# include <stdint.h>
# include <stdint.h>
# include "s_data.h"
# include "s_cmd.h"

uint8_t	builtin_export(t_data *_Nonnull data, t_cmd cmd,
			int32_t *_Nonnull pipe_fd, bool in_child);

#endif
