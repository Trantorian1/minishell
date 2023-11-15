/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:46:27 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:43:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_main.h"

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

#include "safe_exit.h"
#include "sigtype.h"

static void	handle_sigint(int32_t sig);

void	sig_main(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("signal");
		safe_exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		safe_exit(EXIT_FAILURE);
	}
}

static void	handle_sigint(int32_t sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
