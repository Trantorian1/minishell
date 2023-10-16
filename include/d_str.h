/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_str.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:16:31 by marvin            #+#    #+#             */
/*   Updated: 2023/09/28 03:17:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef D_STRING_H
# define D_STRING_H

# define PROMPT_DEFAULT "minishell: "
# define PROMPT_HEREDOC "> "
# define HEREDOC "<<"

# define PIPE (char[]) {-128, '\0'}
# define QUOTE_SINGLE (char[]) {-127, '\0'}
# define QUOTE_DOUBLE (char[]) {-126, '\0'}
# define WHITESPACE (char[]) {-125, '\0'}

# define REDIR_HEREDOC "<<"
# define REDIR_IN "<"
# define REDIR_APPEND ">>"
# define REDIR_OUT ">"

# define ERR_STR "Error: unterminated string at index %zu\n"
# define ERR_REDIR "Error: redirection with unspecified output/input at index %zu\n"
# define ERR_PIPE "Error: pipe-terminated command\n" 
# define ERR_EXPORT "Error: invalid variable format\n"

#endif // !D_STRING_H
