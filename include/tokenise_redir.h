/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_redir.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:37:09 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 08:45:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_REDIR_H
# define TOKENISE_REDIR_H

# include <stdint.h>
# include <stddef.h>
# include "dynamic/vector.h"
# include "dynamic/string.h"
# include "s_data.h"

uint8_t	tokenise_redir(
	t_data *_Nonnull data,
	size_t *_Nonnull i,
	uint8_t *_Nonnull command,
	t_str input
);

#endif
