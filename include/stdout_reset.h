/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_reset.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:12:14 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 12:51:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDOUT_RESTORE_H
# define STDOUT_RESTORE_H

# include <stdint.h>

uint8_t	stdout_reset(int32_t fd_old, int32_t fd_new);

#endif
