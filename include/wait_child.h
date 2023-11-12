/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:04:54 by marvin            #+#    #+#             */
/*   Updated: 2023/11/12 15:15:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAIT_CHILD_H
# define WAIT_CHILD_H

# include <stdint.h>
# include <sys/types.h>

int32_t	wait_child(pid_t pid_last);

#endif
