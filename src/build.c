/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:44:39 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 11:46:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <readline/readline.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"

uint8_t	build(void);

uint8_t	build(void)
{
	t_vptr	*vstr;
	t_cstr	input;
	size_t	index;

	vstr = vptr_create(t_str, 0);

	input = readline("> ");
	while (input != NULL && ! cstr_eq(input, "EXIT"))
	{
		vstr_append(vstr, str_create(input));
		free(input);
		input = readline("> ");
	}
	free(input);

	index = 0;
	while (index < vstr->len)
	{
		printf("%zu:'%s'\n", index, vptr_get(t_str, vstr, index).get);
		index++;
	}
	vstr_destroy(vstr);

	return (EXIT_SUCCESS);
}
