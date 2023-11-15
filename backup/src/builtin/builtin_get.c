/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:48:32 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 11:30:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_get.h"

#include <stdio.h>

t_builtin	builtin_get(t_cstr _Nonnull cmd)
{
	if (cmd == NULL)
		return (BUILTIN_NONE);
	if (cstr_eq(cmd, "exit"))
		return (BUILTIN_EXIT);
	else if (cstr_eq(cmd, "echo"))
		return (BUILTIN_ECHO);
	else if (cstr_eq(cmd, "export"))
		return (BUILTIN_EXPORT);
	else if (cstr_eq(cmd, "env"))
		return (BUILTIN_ENV);
	else if (cstr_eq(cmd, "unset"))
		return (BUILTIN_UNSET);
	else if (cstr_eq(cmd, "pwd"))
		return (BUILTIN_PWD);
	else if (cstr_eq(cmd, "cd"))
		return (BUILTIN_CD);
	return (BUILTIN_NONE);
}
