/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_pipe.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 07:28:21 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:11:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_PIPE_H
# define TOKENISE_PIPE_H

# include <stdint.h>
# include <stddef.h>
# include "dynamic/vector.h"
# include "dynamic/string.h"
# include "s_data.h"

uint8_t	tokenise_pipe(t_data *_Nonnull data, size_t *_Nonnull i,
			uint8_t *_Nonnull command, t_str input);

#endif
