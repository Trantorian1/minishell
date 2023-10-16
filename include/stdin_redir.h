/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_redir.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:32:58 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 13:33:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDIN_REDIR_H
# define STDIN_REDIR_H

# include <stdint.h>

uint8_t	stdin_redir(int32_t *_Nonnull fd_old, int32_t *_Nonnull fd_new);

#endif
