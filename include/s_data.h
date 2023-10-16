/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_data.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 08:15:06 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 12:37:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_DATA_H
# define S_DATA_H

# include <stdint.h>
# include "dynamic/vector.h"
# include "dynamic/string.h"

// TODO: pack this!!!

typedef struct s_data
{
	uint8_t				error_code;
	uint8_t				exit;
	size_t				index_line;
	t_vptr *_Nonnull	user_input;
	t_vptr *_Nonnull	arg;
	t_vptr *_Nonnull	redir;
	// t_env *_Nonnull		env;
}	t_data;

#endif // !S_DATA_H

