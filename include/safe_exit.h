/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:51:16 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 13:54:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_EXIT_H
# define SAFE_EXIT_H

# include <stdint.h>

_Noreturn void	safe_exit(uint8_t error);

#endif
