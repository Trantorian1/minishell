/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_send.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:16:01 by marvin            #+#    #+#             */
/*   Updated: 2023/09/18 08:31:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDIN_SEND_H
# define STDIN_SEND_H

# include <stdint.h>
# include "dynamic/string.h"

uint32_t	stdin_send(char *_Nonnull cstr, int32_t fd);

#endif // !STDIN_SEND_H
