/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:46:08 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:57:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_loop.h"

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

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

static bool	g_in_exec = false;

static inline void		setup_signals(void);

void		main_loop(t_data *_Nonnull data)
{
	while (!data->should_exit)
	{
		setup_signals();
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
			g_in_exec = true;
			setup_signals();
			state_exec(data);
			g_in_exec = false;
			setup_signals();
			state_cleanup(data);
		}
		state_reset(data);
	}
}

static void		handle_sigint(int32_t sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\n", 1);
	if (g_in_exec == false)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void		handle_sigquit(int32_t sig)
{
	(void)sig;
	rl_redisplay();
}

static inline void		setup_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);

	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		safe_exit(EXIT_FAILURE);
	}

	if (g_in_exec == true)
		signal(SIGQUIT, handle_sigquit);
	else
		signal(SIGQUIT, SIG_IGN);
}
