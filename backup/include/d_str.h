/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_str.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:16:31 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 17:59:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef D_STR_H
# define D_STR_H

# define PROMPT_DEFAULT "minishell: "
# define PROMPT_HEREDOC "> "
# define HEREDOC "<<"

# define PIPE "\x80"
# define QUOTE_SINGLE "\x81"
# define QUOTE_DOUBLE "\x82"
# define WHITESPACE "\x83"

# define REDIR_HEREDOC "<<"
# define REDIR_IN "<"
# define REDIR_APPEND ">>"
# define REDIR_OUT ">"

#endif
