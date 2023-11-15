/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:26:24 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 19:49:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_exec_path.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "env_get.h"

static inline t_str	search_in_path(t_vptr *_Nonnull env, t_cstr _Nonnull exec);

t_str	get_exec_path(t_vptr *_Nonnull env, t_cstr _Nonnull exec)
{
	if (env == NULL || exec == NULL || env->len == 0)
		return (str_create(""));
	if (access(exec, F_OK) == 0 || *exec == '\0')
		return (str_create(exec));
	return (search_in_path(env, exec));
}

static inline t_str	search_in_path(t_vptr *_Nonnull env, t_cstr _Nonnull exec)
{
	t_vptr		*path;
	size_t		index;
	t_str		file;
	bool		found;

	path = str_split(env_get(env, "PATH"), ":");
	file = str_create("");
	index = (size_t)(-1);
	found = false;
	while (found == false || ++index < path->len)
	{
		str_rm(&file, 0, file.len);
		str_append_str(&file, (*(t_str *)vptr_get(path, index)).get);
		str_append_str(&file, "/");
		str_append_str(&file, exec);
		if (access(file.get, F_OK) == 0)
			found = true;
	}
	if (found == false)
	{
		str_rm(&file, 0, file.len);
		str_append_str(&file, exec);
	}
	vstr_destroy(path);
	return (file);
}
