/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:42:51 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 20:54:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

#include "data_get.h"
#include "s_env.h"
#include "state_parse.h"
#include "state_tokenise.h"
#include "state_heredoc.h"
#include "state_expand.h"
#include "state_unquote.h"
#include "state_collect.h"
#include "state_exec.h"
#include "state_cleanup.h"
#include "state_reset.h"

#include "dynamic/alloc.h"
#include "env_destroy.h"
#include "env_create.h"
#include "env_collect.h"
#include "safe_exit.h"
#include "main_loop.h"

#include "s_data.h"

int32_t	main(int32_t argc, t_cstr *argv, t_cstr *envp)
{
	t_data	*data;

	data = data_get();
	(void)argc;
	(void)argv;
	data->env = (t_vptr * _Nonnull)env_create(envp);
	if (main_loop(data) == EXIT_FAILURE)
		printf("exit\n");
	rl_clear_history();
	state_cleanup(data);
	env_destroy(data->env);
	state_reset(data);
	safe_free_all();
	rl_clear_history();
	return (data->exit_code);
}
