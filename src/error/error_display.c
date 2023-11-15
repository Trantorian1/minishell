/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:04:36 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 19:10:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_display.h"

#include <stdlib.h>
#include <unistd.h>

#include "data_get.h"
#include "dynamic/string.h"

uint8_t	error_display(
	t_cstr _Nonnull cmd,
	t_cstr _Nonnull err,
	uint8_t code
) {
	t_str	display;

	if (cmd == NULL || err == NULL)
		return (EXIT_FAILURE);
	data_get()->exit_code = code;
	display = str_create("minishell: ");
	str_append_str(&display, cmd);
	str_append_str(&display, ": ");
	str_append_str(&display, err);
	str_append_char(&display, '\n');
	write(STDERR_FILENO, display.get, display.len);
	str_destroy(&display);
	return (EXIT_FAILURE);
}
