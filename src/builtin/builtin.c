/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:42:35 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 22:14:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#include <stdlib.h>

#include "dynamic/string.h"
#include "builtin_echo.h"
#include "builtin_exit.h"
#include "builtin_export.h"
#include "builtin_env.h"
#include "builtin_unset.h"
#include "builtin_pwd.h"
#include "builtin_cd.h"

#include "e_builtin.h"

uint8_t	builtin(t_data *_Nonnull data, t_cmd cmd, t_builtin type)
{
	if (data == NULL)
		return (EXIT_FAILURE);

	(void)cmd;
	if (type == BUILTIN_NONE)
		return (EXIT_SUCCESS);
	if (type == BUILTIN_EXIT)
		return (builtin_exit(data));
	if (type == BUILTIN_ECHO)
		return (builtin_echo(data, cmd));
	if (type == BUILTIN_EXPORT)
		return (builtin_export(data, cmd));
	if (type == BUILTIN_ENV)
		return (builtin_env(data, cmd));
	if (type == BUILTIN_UNSET)
		return (builtin_unset(data, cmd));
	if (type == BUILTIN_PWD)
		return (builtin_pwd(data, cmd));
	if (type == BUILTIN_CD)
		return (builtin_cd(data, cmd));

	return (EXIT_SUCCESS);
}
