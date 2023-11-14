/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:46:08 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:43:46 by marvin           ###   ########.fr       */
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

uint8_t	main_loop(t_data *_Nonnull data)
{
	uint8_t	err_code;

	err_code = EXIT_SUCCESS;
	while (!data->should_exit)
	{
		sig_main();

		err_code = state_parse(data);
		if (err_code == EXIT_FAILURE)
			break ;

		while (data->index_line < data->user_input->len)
		{
			if (state_tokenise(data))
				break ;
			state_heredoc(data);
			state_expand(data);
			state_unquote(data);
			state_collect(data);
			if (g_sigtype != SIGINT)
			{
				sig_exec();
				state_exec(data);
				sig_main();
			}
			g_sigtype = SIGNONE;

			state_cleanup(data);
		}
		state_reset(data);
	}

	return (err_code);
}
