/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:49:55 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 18:51:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include <stdint.h>
# include "s_data.h"
# include "s_cmd.h"

uint8_t	builtin_cd(t_data *_Nonnull data, t_cmd cmd);

#endif
