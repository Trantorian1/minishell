/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_tokenise.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:41:10 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 07:41:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_TOKENISE_H
# define STATE_TOKENISE_H

# include <stdint.h>
# include "dynamic/string.h"
# include "s_data.h"

# define PREV 0
# define CURR 1

uint8_t	state_tokenise(t_data *_Nonnull data);

#endif
