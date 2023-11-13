/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vstr_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:14:29 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 16:19:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vstr_display.h"

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"

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
		str_append_str(&display, vptr_get(t_str, vstr, index).get);
		str_append_char(&display, '\n');
		write(STDOUT_FILENO, display.get, display.len);

		str_rm(&display, 0, display.len);
		index++;
	}

	str_destroy(&display);
}
