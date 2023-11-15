/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_read.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:04:06 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 10:09:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDOUT_READ_H
# define STDOUT_READ_H

# include <stdint.h>
# include "dynamic/string.h"

uint8_t	stdout_read(t_str *_Nonnull str, int32_t fd);

#endif
