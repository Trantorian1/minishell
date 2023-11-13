/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:51:57 by marvin            #+#    #+#             */
/*   Updated: 2023/11/13 21:34:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#include "d_pipe.h"
#include "dynamic/string.h"
#include "dynamic/vector.h"
#include "env_get.h"
#include "env_update.h"
#include "error_display.h"
#include "safe_close.h"

static uint8_t	cd_no_home(void);
static uint8_t	cd_to(
	t_cstr _Nonnull dst, 
	t_vptr *_Nonnull env
);
static uint8_t	cd_relative(
	t_cstr _Nonnull dst, 
	t_cstr _Nonnull home, 
	t_vptr *_Nonnull env
);

uint8_t	builtin_cd(t_data *_Nonnull data, t_cmd cmd, int32_t *_Nonnull pipe_fd)
{
	t_str	home;

	(void)pipe_fd;

	if (data == NULL || pipe_fd == NULL)
		return (EXIT_FAILURE);

	safe_close(pipe_fd[PIPE_WRITE]);
	safe_close(pipe_fd[PIPE_READ]);
	
	home = env_get(data->env, "HOME");
	if (cmd.arg[1] == NULL)
	{
		if (str_eq(home, ""))
			return (cd_no_home());
		else
			return (cd_to(home.get, data->env));
	}
	else if (cmd.arg[2] == NULL)
	{
		if (cmd.arg[1][0] == '~')
			return (cd_relative(cmd.arg[1], home.get, data->env));
		else
			return (cd_to(cmd.arg[1], data->env));
	}
	
	error_display("cd", "too many arguments");
	return (EXIT_FAILURE);
}

static void	update_env(
	t_vptr *_Nonnull env, 
	t_cstr _Nonnull oldpwd, 
	t_cstr _Nonnull newpwd
) {
	t_str	pair_pwd;

	pair_pwd = str_create("");

	str_append_str(&pair_pwd, "OLDPWD=");
	str_append_str(&pair_pwd, oldpwd);
	env_update(env, pair_pwd.get);

	str_rm(&pair_pwd, 0, pair_pwd.len);

	str_append_str(&pair_pwd, "PWD=");
	str_append_str(&pair_pwd, newpwd);
	env_update(env, pair_pwd.get);

	str_destroy(&pair_pwd);
}

static uint8_t	cd_no_home(void)
{
	error_display("cd", "HOME not set");
	return (EXIT_FAILURE);
}

static uint8_t	cd_to(t_cstr _Nonnull dst, t_vptr *_Nonnull env)
{
	char	oldpwd[2048];
	char	newpwd[2048];

	if (dst == NULL || env == NULL)
		return (EXIT_FAILURE);

	if (getcwd(oldpwd, 2048) == NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}

	if (chdir(dst) < 0)
	{
		perror("chdir");
		return (EXIT_FAILURE);
	}
	
	if (getcwd(newpwd, 2048) == NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}

	update_env(env, oldpwd, newpwd);

	return (EXIT_SUCCESS);
}

static uint8_t	cd_relative(
	t_cstr _Nonnull dst, 
	t_cstr _Nonnull home, 
	t_vptr *_Nonnull env
) {
	t_str	absolute;

	if (dst == NULL || home == NULL || env == NULL)
		return (EXIT_FAILURE);

	absolute = str_create(home);
	str_append_str(&absolute, "/");
	str_append_str(&absolute, dst + 1);
	cd_to(absolute.get, env);

	str_destroy(&absolute);
	return (EXIT_SUCCESS);
}
