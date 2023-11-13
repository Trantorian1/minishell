/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:42:35 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 13:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#include <stdlib.h>

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

static f_builtin	g_builtins[E_BUILTIN_SIZE] = {
	builtin_none,
	builtin_echo,
	builtin_cd,
	builtin_pwd,
	builtin_export,
	builtin_unset,
	builtin_env,
	builtin_exit
};

uint8_t	builtin(t_data *_Nonnull data, t_cmd cmd, t_builtin type, int32_t *_Nonnull pipe_fd)
{
	if (data == NULL)
		return (EXIT_FAILURE);

	g_builtins[type](data, cmd, pipe_fd);

	return (EXIT_SUCCESS);
}
