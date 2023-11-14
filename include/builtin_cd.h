/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:49:55 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 00:42:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include <stdint.h>
# include <stdbool.h>
# include "s_data.h"
# include "s_cmd.h"

uint8_t	builtin_cd(
	t_data *_Nonnull data, 
	t_cmd cmd, 
	int32_t *_Nonnull pipe_fd,
	bool in_child
);

#endif
