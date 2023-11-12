/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:04:36 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 12:08:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_display.h"

#include <stdlib.h>
#include <unistd.h>

// uint8_t	error_display(t_cstr _Nonnull cmd, t_cstr _Nonnull err)
// {
// 	if (cmd == NULL || err == NULL)
// 		return (EXIT_FAILURE);
//
// 	write(STDERR_FILENO, "minishell: ", 12);
// 	write(STDERR_FILENO, cmd, cstr_len(cmd))
//
// 	"minishell: {cmd}: {err}"
//
// 	return (EXIT_FAILURE);
// }
