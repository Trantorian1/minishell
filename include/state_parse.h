/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:55:36 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:13:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_PARSE_H
# define STATE_PARSE_H

# include <stdint.h>
# include "dynamic/string.h"
# include "s_data.h"

uint8_t					state_parse(t_data *_Nonnull data);

#endif
