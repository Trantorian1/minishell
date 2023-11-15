/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_reset.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:12:14 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:08:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDOUT_RESET_H
# define STDOUT_RESET_H

# include <stdint.h>

uint8_t	stdout_reset(int32_t fd_old, int32_t fd_new);

#endif
