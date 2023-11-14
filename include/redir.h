/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:12:00 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 13:20:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_HEREDOC_H
# define REDIR_HEREDOC_H

# include <stdint.h>
# include "s_cmd.h"

uint8_t	redir(t_cmd cmd, int32_t *_Nonnull pipes);

#endif
