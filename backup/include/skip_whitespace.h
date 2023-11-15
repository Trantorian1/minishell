/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 07:44:13 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 07:45:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKIP_WHITESPACE_H
# define SKIP_WHITESPACE_H

# include <stddef.h>
# include "dynamic/string.h"

size_t	skip_whitespace(t_str str, size_t i_curr);

#endif
