/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_quote.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 06:52:17 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:09:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_QUOTE_H
# define TOKENISE_QUOTE_H

# include <stdint.h>

# include "dynamic/vector.h"

uint8_t	tokenise_quote(t_vptr *_Nonnull vptr, size_t *_Nonnull i, t_str input,
			char c);

#endif
