/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_reset.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:31:40 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 13:32:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDIN_RESET_H
# define STDIN_RESET_H

# include <stdint.h>

int32_t	stdin_reset(int32_t fd_old, int32_t fd_new);

#endif
