/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:53:38 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 21:21:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_pwd.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "dynamic/string.h"

uint8_t	builtin_pwd(t_data *_Nonnull data, t_cmd cmd)
{
	char	cwd[2048];

	(void)data;
	(void)cmd;

	if (getcwd(cwd, 2045) == NULL)
	{
		write(STDERR_FILENO, "minishell: could not get cwd\n", 30);
		perror("getcwd");
		return (EXIT_FAILURE);
	}

	write(STDOUT_FILENO, cwd, cstr_len(cwd));
	write(STDOUT_FILENO, "\n", 1);

	return (EXIT_SUCCESS);
}
