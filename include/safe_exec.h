/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:17:39 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 19:21:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_EXEC_H
# define SAFE_EXEC_H

# include <stdint.h>
# include "dynamic/string.h"

# include "s_data.h"
# include "s_cmd.h"

uint8_t	safe_exec(t_data *_Nonnull data, t_cmd cmd);

#endif