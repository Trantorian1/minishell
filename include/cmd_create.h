/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 01:05:13 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 01:06:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_CREATE_H
# define CMD_CREATE_H

# include "s_cmd.h"
# include "dynamic/string.h"

t_cmd	cmd_create(t_cstr *_Nonnull arg, t_cstr *_Nonnull redir);

#endif
