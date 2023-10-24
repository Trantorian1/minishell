/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:42:51 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 22:29:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "state_parse.h"
#include "env_create.h"
#include "s_data.h"

static t_data	g_data = {
	.error_code  = EXIT_SUCCESS,
	.exit        = false,
	.index_line  = 0,
	.user_input  = NULL,
	.arg         = NULL,
	.redir       = NULL,
};

int32_t		main(int32_t argc, t_cstr *argv, t_cstr *envp)
{
	(void)argc;
	(void)argv;

	g_data.env = (t_vptr *_Nonnull)env_create(envp);

	while (!g_data.exit)
	{
		if (state_parse(&g_data) == EXIT_FAILURE)
			continue ;
		vstr_destroy(g_data.user_input);
	}
	rl_clear_history();

	return (EXIT_SUCCESS);
}
