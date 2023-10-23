/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:19:29 by marvin            #+#    #+#             */
/*   Updated: 2023/10/23 13:23:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delim_str.h"

#include "dynamic/string.h"
#include "d_str.h"

t_cstr _Nonnull	delim_str(t_str str)
{
	if (str_eq(str, PIPE))
		return ("PIPE");
	else if (str_eq(str, QUOTE_SINGLE))
		return ("QUOTE_SINGLE");
	else if (str_eq(str, QUOTE_DOUBLE))
		return ("QUOTE_DOUBLE");
	else if (str_eq(str, WHITESPACE))
		return ("WHITESPACE");

	return (str.get);
}
