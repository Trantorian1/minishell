/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pipe.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:34:35 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 16:36:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_PIPE_H
# define SAFE_PIPE_H

# include <stdint.h>

int32_t	safe_pipe(int32_t pipefd[2]);

#endif
