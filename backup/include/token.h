/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:17:59 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:54:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "dynamic/string.h"

t_cstr _Nonnull	token_quote_single(void);
t_cstr _Nonnull	token_quote_double(void);
t_cstr _Nonnull	token_pipe(void);

#endif
