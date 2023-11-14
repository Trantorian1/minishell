/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vstr_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:14:29 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:42:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vstr_display.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#include "builtin_get.h"
#include "delim_str.h"
#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "e_builtin.h"

void	vstr_display(t_vptr *_Nonnull vstr)
{
	size_t	index;
	t_str	display;

	if (vstr == NULL)
		return ;
	index = 0;
	display = str_create("");
	while (index < vstr->len)
	{
		str_append_char(&display, '\'');
		str_append_str(&display, delim_str(vptr_get(t_str, vstr, index)));
		str_append_char(&display, '\'');
		str_append_char(&display, '\n');
		index++;
	}
	write(STDOUT_FILENO, display.get, display.len);
	str_destroy(&display);
}
