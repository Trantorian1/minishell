/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 03:26:24 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 04:12:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_exec_path.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"
#include "env_get.h"

/**
 * @brief Finds the absolute path to a file.
 *
 * @param env (t_vptr *_Nonnull): environtment vector.
 * @param exec (t_cstr _Nonnull): file name.
 * @return (t_str): absolute path to the file if it exists, bogus path
 * otherwise.
 */
t_str	get_exec_path(t_vptr *_Nonnull env, t_cstr _Nonnull exec)
{
	t_vptr		*path;
	size_t		index;
	t_str		file;

	if (env == NULL || exec == NULL)
		return (str_create(""));

	path = str_split(env_get(env, "PATH"), ":");
	file = str_create("");
	if (access(exec, F_OK) == 0)
		return (str_create(exec));

	index = 0;
	while (index < path->len)
	{
		str_rm(&file, 0, file.len);
		str_append_str(&file, vptr_get(t_str, path, index).get);
		str_append_str(&file, "/");
		str_append_str(&file, exec);

		if (access(file.get, F_OK) == 0)
			break ;

		index++;
	}

	vstr_destroy(path);
	return (file);
}
