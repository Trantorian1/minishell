/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:46:08 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 04:13:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_loop.h"

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "sigtype.h"
#include "state_parse.h"
#include "state_tokenise.h"
#include "state_heredoc.h"
#include "state_expand.h"
#include "state_unquote.h"
#include "state_collect.h"
#include "state_exec.h"
#include "state_cleanup.h"
#include "state_reset.h"

#include "safe_exit.h"
#include "vstr_display.h"
#include "sig_main.h"
#include "sig_exec.h"

void		main_loop(t_data *_Nonnull data)
{
	while (!data->should_exit)
	{
		sig_main();
		if (state_parse(data) == EXIT_FAILURE)
			break ;
		while (data->index_line < data->user_input->len)
		{
			if (state_tokenise(data))
				break ;
			state_heredoc(data);
			state_expand(data);
			state_unquote(data);
			state_collect(data);

			if (sigtype != SIGINT)
			{
				sig_exec();
				state_exec(data);
				sig_main();
			}

			state_cleanup(data);
		}
		state_reset(data);
	}
}
