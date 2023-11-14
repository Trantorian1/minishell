/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:10:37 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 00:59:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_exit.h"

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "safe_close.h"
#include "safe_exit.h"
#include "state_cleanup.h"
#include "env_destroy.h"
#include "error_display.h"

#include "d_pipe.h"

static inline void	exit_impl(t_data *_Nonnull data, uint8_t code);

uint8_t	builtin_exit(
	t_data *_Nonnull data, 
	t_cmd cmd, 
	int32_t *_Nonnull pipe_fd,
	bool in_child
) {
	int64_t	code;

	(void)pipe_fd;

	if (data == NULL || pipe_fd == NULL)
		return (EXIT_FAILURE);

	code = EXIT_SUCCESS;
	if (cmd.arg[1] != NULL)
	{
		code = 2;
		if (cstr_to_i64(cmd.arg[1], &code) == EXIT_FAILURE)
			error_display("exit", "numeric argument required");
		else if (cmd.arg[2] != NULL)
			error_display("exit", "too many arguments");
	}

	if (in_child == false)
		write(pipe_fd[PIPE_WRITE], "exit\n", 5);
	if (cmd.arg[1] == NULL || cmd.arg[2] == NULL || code == 2)
	{
		safe_close(pipe_fd[PIPE_WRITE]);
		safe_close(pipe_fd[PIPE_READ]);
		exit_impl(data, (uint8_t)code);
	}

	return (EXIT_FAILURE);
}

static inline _Noreturn void	exit_impl(t_data *_Nonnull data, uint8_t code)
{
	state_cleanup(data);
	vstr_destroy(data->user_input);
	env_destroy(data->env);
	rl_clear_history();

	// TODO: replace this with safe_exit (only for testing purposes rn)
	exit(code);
}
