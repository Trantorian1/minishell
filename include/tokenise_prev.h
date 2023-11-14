/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_prev.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 06:55:32 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 06:58:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_PREV_H
# define TOKENISE_PREV_H

# include <stddef.h>
# include <stdint.h>
# include "dynamic/vector.h"
# include "dynamic/string.h"

uint8_t	tokenise_prev(
	t_vptr *_Nonnull vptr,
	t_str input,
	size_t i_prev,
	size_t i_curr
);

#endif
