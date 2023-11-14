/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_whitespace.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:05:02 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 09:10:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_WHITESPACE_H
# define TOKENISE_WHITESPACE_H

# include <stddef.h>
# include "dynamic/vector.h"
# include "dynamic/string.h"

uint8_t	tokenise_whitespace(
	t_vptr *_Nonnull vptr,
	size_t *_Nonnull i,
	uint8_t *_Nonnull command,
	t_str input
);

#endif
