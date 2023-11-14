/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_none.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:40:25 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 00:46:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_NONE_H
# define BUILTIN_NONE_H

# include <stdint.h>
# include <stdbool.h>
# include "s_data.h"
# include "s_cmd.h"

uint8_t	builtin_none(
	t_data *_Nonnull data, 
	t_cmd cmd, 
	int32_t *_Nonnull pipe_fd,
	bool in_child
);

#endif
