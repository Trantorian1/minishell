/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:42:35 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:11:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#include <stdlib.h>

#include "builtin_get.h"
#include "d_pipe.h"
#include "dynamic/string.h"
#include "builtin_none.h"
#include "builtin_echo.h"
#include "builtin_cd.h"
#include "builtin_pwd.h"
#include "builtin_export.h"
#include "builtin_env.h"
#include "builtin_exit.h"
#include "builtin_unset.h"

#include "e_builtin.h"
#include "safe_close.h"

static t_f_builtin	g_builtins[E_BUILTIN_SIZE] = {
	builtin_none,
	builtin_echo,
	builtin_cd,
	builtin_pwd,
	builtin_export,
	builtin_unset,
	builtin_env,
	builtin_exit
};

uint8_t	builtin(
	t_data *_Nonnull data,
	t_cmd cmd,
	int32_t *_Nonnull pipe_fd,
	bool in_child
) {
	uint8_t		err_code;
	t_builtin	type;

	if (data == NULL)
		return (EXIT_FAILURE);
	type = builtin_get(cmd.arg[0]);
	err_code = g_builtins[type](data, cmd, pipe_fd, in_child);
	safe_close(pipe_fd[PIPE_READ]);
	safe_close(pipe_fd[PIPE_WRITE]);
	return (err_code);
}
