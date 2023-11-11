/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:48:32 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 20:05:52 by marvin           ###   ########.fr       */
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

	return (BUILTIN_NONE);
}
