/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:01:44 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:43:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_exec.h"
#include "safe_exit.h"

#include <readline/readline.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void	handle_sigint(int32_t sig);
static void	handle_sigquit(int32_t sig);

void	sig_exec(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("signal");
		safe_exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
	{
		perror("signal");
		safe_exit(EXIT_FAILURE);
	}
}

static void	handle_sigint(int32_t sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

static void	handle_sigquit(int32_t sig)
{
	(void)sig;
	rl_redisplay();
}
