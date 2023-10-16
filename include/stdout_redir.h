/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_redir.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:25:10 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 11:45:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDOUT_REDIR_H
# define STDOUT_REDIR_H

# include <stdint.h>
# include "dynamic/string.h"

uint8_t	stdout_redir(int32_t *_Nonnull fd_old, int32_t *_Nonnull fd_new);

#endif
