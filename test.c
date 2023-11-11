/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:04:52 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 17:12:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "dynamic/string.h"
#include "dynamic/vector.h"

#include "state_tokenise.h"
#include "state_heredoc.h"
#include "state_expand.h"
#include "state_unquote.h"
#include "state_collect.h"
#include "state_exec.h"
#include "state_cleanup.h"

#include "env_create.h"
#include "env_get.h"
#include "env_update.h"
#include "env_destroy.h"
#include "state_parse.h"
#include "stdin_redir.h"
#include "stdin_send.h"
#include "stdin_reset.h"
#include "delim_str.h"
#include "get_exec_path.h"

#include "s_data.h"
#include "s_env.h"
#include "s_cmd.h"

int	main(int32_t argc, t_cstr *argv, t_cstr *envp)
{
	t_data	data = {
		.exit = 0,
		.index_line = 0,
		.user_input = NULL,
		.arg = NULL,
		.redir = NULL
	};

	(void)argc;
	(void)argv;

	data.env = (t_vptr *_Nonnull)env_create(envp);

	state_parse(&data);
	state_tokenise(&data);
	state_heredoc(&data);
	state_expand(&data);
	state_unquote(&data);
	state_collect(&data);
	state_exec(&data);
	state_cleanup(&data);

	return (EXIT_FAILURE);
}
