/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:01:44 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 00:09:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_exec.h"

#include <readline/readline.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>

static void	handle_sigint(int32_t sig);
static void	handle_sigquit(int32_t sig);

void	sig_exec(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
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
