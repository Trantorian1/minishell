/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_get.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 05:45:08 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 05:46:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELIMITER_GET_H
# define DELIMITER_GET_H

# include <stddef.h>

# include "dynamic/vector.h"
# include "dynamic/string.h"

t_str	delimiter_get(t_vptr *_Nonnull redir, size_t i_curr);

#endif
