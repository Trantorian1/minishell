/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:02:54 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 12:04:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_DISPLAY_H
# define ERROR_DISPLAY_H

# include <stdint.h>
# include "dynamic/string.h"

uint8_t	error_display(t_cstr _Nonnull cmd, t_cstr _Nonnull err);

#endif
