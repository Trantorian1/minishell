/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:27:00 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 04:24:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_heredoc.h"
#include "safe_exit.h"
#include "sig_main.h"

#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sigtype.h"

uint8_t	sigtype = SIGNONE;

static void	handle_sigint(int32_t sig);

void	sig_heredoc(void)
{
	if (signal(SIGINT, &handle_sigint) == SIG_ERR)
	{
		perror("signal");
		safe_exit(EXIT_FAILURE);
	}
}

static void	handle_sigint(int32_t sig)
{
	(void)sig;

	close(STDIN_FILENO);
	sigtype = SIGINT;
}
