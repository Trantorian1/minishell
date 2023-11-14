/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:14:44 by marvin            #+#    #+#             */
/*   Updated: 2023/11/14 13:21:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "d_str.h"
#include "dynamic/vector.h"
#include "safe_pipe.h"
#include "safe_close.h"

#include "d_pipe.h"

static inline uint8_t	redir_heredoc(t_str content, int32_t pipes[2]);

static inline uint8_t	redir_file(t_str file, int32_t flags,
							int32_t	*_Nonnull pipes);

uint8_t	redir(t_cmd cmd, int32_t pipes[2])
{
	size_t	index;
	t_str	*redir;
	t_str	content;

	index = 0;
	while (index < cmd.redir->len)
	{
		redir = vptr_get_ptr(t_str, cmd.redir, index);
		content = *(redir + 1);
		if (str_eq(*redir, REDIR_HEREDOC) && redir_heredoc(content, pipes))
			return (EXIT_FAILURE);
		else if (str_eq(*redir, REDIR_IN)
			&& redir_file(content, O_RDONLY, pipes))
			return (EXIT_FAILURE);
		else if (str_eq(*redir, REDIR_APPEND)
			&& redir_file(content, O_WRONLY | O_APPEND | O_CREAT, pipes))
			return (EXIT_FAILURE);
		else if (str_eq(*redir, REDIR_OUT)
			&& redir_file(content, O_WRONLY | O_CREAT | O_TRUNC, pipes))
			return (EXIT_FAILURE);
		index += 2;
	}
	return (EXIT_SUCCESS);
}

static inline uint8_t	redir_heredoc(t_str content, int32_t pipes[2])
{
	int32_t	pipe_id[2];

	safe_pipe(pipe_id);
	safe_close(pipes[PIPE_READ]);
	if (write(pipe_id[PIPE_WRITE], content.get, content.len) < 0)
	{
		perror("could not write to heredoc");
		safe_close(pipe_id[PIPE_WRITE]);
		return (EXIT_FAILURE);
	}
	pipes[PIPE_READ] = pipe_id[PIPE_READ];
	safe_close(pipe_id[PIPE_WRITE]);
	return (EXIT_SUCCESS);
}

static inline uint8_t	redir_file(
	t_str file,
	int32_t flags,
	int32_t	*_Nonnull pipes
) {
	int32_t	fd;

	fd = open(file.get, flags, S_IWUSR | S_IRUSR);
	if (flags == (O_RDONLY))
	{
		safe_close(pipes[PIPE_READ]);
		pipes[PIPE_READ] = fd;
	}
	else
	{
		safe_close(pipes[PIPE_WRITE]);
		pipes[PIPE_WRITE] = fd;
	}
	if (fd < 0)
	{
		perror(file.get);
		if (flags == (O_RDONLY))
			safe_close(pipes[PIPE_WRITE]);
		else
			safe_close(pipes[PIPE_READ]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
