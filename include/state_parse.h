/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:55:36 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 12:30:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdint.h>
# include "dynamic/string.h"
# include "s_data.h"

uint8_t					state_parse(t_data *_Nonnull data);

#endif
