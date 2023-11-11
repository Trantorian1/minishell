/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:27:31 by marvin            #+#    #+#             */
/*   Updated: 2023/11/11 20:05:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_BUILTIN_H
# define E_BUILTIN_H

typedef enum e_builtin
{
	BUILTIN_NONE,
	BUILTIN_EXIT,
	BUILTIN_ECHO,
	BUILTIN_EXPORT,
	BUILTIN_ENV,
	E_BUILTIN_SIZE
}	t_builtin;

#endif
