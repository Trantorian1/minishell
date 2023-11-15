/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:19:04 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:49:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_cstr _Nonnull	token_quote_single(void)
{
	return ((char []){-127, '\0'});
}

t_cstr _Nonnull	token_quote_double(void)
{
	return ((char []){-126, '\0'});
}

t_cstr _Nonnull	token_pipe(void)
{
	return ((char []){-12, '\0'});
}
