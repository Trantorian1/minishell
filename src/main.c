/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:42:51 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 16:23:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "dynamic/alloc.h"
#include "env_collect.h"
#include "state_parse.h"
#include "state_tokenise.h"
#include "state_heredoc.h"
#include "state_expand.h"
#include "state_unquote.h"
#include "state_collect.h"
#include "state_exec.h"
#include "state_cleanup.h"

#include "env_destroy.h"
#include "env_create.h"

#include "s_data.h"

static inline void	reset(t_data *_Nonnull data);

int32_t		main(int32_t argc, t_cstr *argv, t_cstr *envp)
{
	static t_data data = {
		.exit_code   = EXIT_SUCCESS,
		.should_exit = false,
		.index_line  = 0,
		.user_input  = NULL,
		.arg         = NULL,
		.redir       = NULL,
	};

	(void)argc;
	(void)argv;

	data.env = (t_vptr *_Nonnull)env_create(envp);

	while (!data.should_exit)
	{
		if (state_parse(&data) == EXIT_FAILURE)
			break ;
		while (data.index_line < data.user_input->len)
		{
			state_tokenise(&data);
			state_heredoc(&data);
			state_expand(&data);
			state_unquote(&data);
			state_collect(&data);
			state_exec(&data);
			state_cleanup(&data);
		}
		reset(&data);
	}
	rl_clear_history();
	state_cleanup(&data);
	env_destroy(data.env);
	reset(&data);

	rl_clear_history();

	return (EXIT_SUCCESS);
}

static inline void	reset(t_data *_Nonnull data)
{
	if (data == NULL)
		return ;

	vstr_destroy(data->user_input);
	data->user_input = NULL;
	data->index_line = 0;
}
