/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:09:52 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_EXIT_H
# define BUILTIN_EXIT_H

# include <stdint.h>
# include "s_data.h"
# include "s_cmd.h"

uint8_t	builtin_exit(t_data *_Nonnull data, t_cmd cmd, int32_t *_Nonnull pipe_fd);

#endif
