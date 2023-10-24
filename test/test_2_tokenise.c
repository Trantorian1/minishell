/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_2_tokenise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:32:15 by marvin            #+#    #+#             */
/*   Updated: 2023/10/23 13:28:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/parameterized.h>
#include <stddef.h>
#include <stdint.h>

#include "dynamic/string.h"
#include "dynamic/vector.h"
#include "state_parse.h"
#include "state_tokenise.h"
#include "stdin_redir.h"
#include "stdin_send.h"
#include "stdin_reset.h"
#include "stdout_disable.h"
#include "stdout_enable.h"

#include "d_str.h"

typedef struct s_param
{
	char *_Nonnull				input; 
	char *_Nonnull *_Nullable	arg; 
	char *_Nonnull *_Nullable	redir; 
}	t_param;

static const t_param	g_param[] = {
	// TEST: single argument
	{
		.input = "cat",
		.arg = (char *[]) {
			"cat",
			NULL
		},
		.redir = (char *[]) {
			NULL
		}
	},
	// TEST: single argument (single quotes)
	{
		.input = "'cat'",
		.arg = (char *[]) {
			QUOTE_SINGLE,
			"cat",
			QUOTE_SINGLE,
			NULL
		},
		.redir = (char *[]) {
			NULL
		}
	},
	// TEST: single argument (double quotes)
	{
		.input = "\"cat\"",
		.arg = (char *[]) {
			QUOTE_DOUBLE,
			"cat",
			QUOTE_DOUBLE,
			NULL
		},
		.redir = (char *[]) {
			NULL
		}
	},
	// TEST: single argument (mixed quotes)
	{
		.input = "'cat '\"test \"here",
		.arg = (char *[]) {
			QUOTE_SINGLE,
			"cat ",
			QUOTE_SINGLE,
			QUOTE_DOUBLE,
			"test ",
			QUOTE_DOUBLE,
			"here",
			NULL
		},
		.redir = (char *[]) {
			NULL
		}
	},
	// TEST: arguments only
	{
		.input = "cat -e -n",
		.arg = (char *[]) {
			"cat",
			WHITESPACE,
			"-e",
			WHITESPACE,
			"-n",
			NULL
		},
		.redir = (char *[]) {
			NULL
		}
	},
	// TEST: arguments only (pipes)
	{
		.input = "cat -e -n | echo test | ls -l",
		.arg = (char *[]) {
			"cat",
			WHITESPACE,
			"-e",
			WHITESPACE,
			"-n",
			WHITESPACE,
			PIPE,
			"echo",
			WHITESPACE,
			"test",
			WHITESPACE,
			PIPE,
			"ls",
			WHITESPACE,
			"-l",
			NULL
		},
		.redir = (char *[]) {
			PIPE,
			PIPE,
			NULL
		}
	},
	// TEST: arguments only (pipes, compact)
	{
		.input = "cat -e -n|echo test|ls -l",
		.arg = (char *[]) {
			"cat",
			WHITESPACE,
			"-e",
			WHITESPACE,
			"-n",
			PIPE,
			"echo",
			WHITESPACE,
			"test",
			PIPE,
			"ls",
			WHITESPACE,
			"-l",
			NULL
		},
		.redir = (char *[]) {
			PIPE,
			PIPE,
			NULL
		}
	},
	// TEST: redirections only
	{
		.input = "< in << heredoc > out >> append",
		.arg = (char *[]) {
			NULL
		},
		.redir = (char *[]) {
			"<",
			"in",
			WHITESPACE,
			"<<",
			"heredoc",
			WHITESPACE,
			">",
			"out",
			WHITESPACE,
			">>",
			"append",
			WHITESPACE,
			NULL
		}
	},
	// TEST: redirections only (quoted)
	{
		.input = "< 'in quot'ed << \"heredoc quoted\" > 'out'' '\"quo\"\"ted\">> append",
		.arg = (char *[]) {
			NULL
		},
		.redir = (char *[]) {
			"<",
			QUOTE_SINGLE, "in quot"       , QUOTE_SINGLE,
			"ed",
			WHITESPACE,
			"<<",
			QUOTE_DOUBLE, "heredoc quoted", QUOTE_DOUBLE,
			WHITESPACE,
			">",
			QUOTE_SINGLE, "out"           , QUOTE_SINGLE,
			QUOTE_SINGLE, " "             , QUOTE_SINGLE,
			QUOTE_DOUBLE, "quo"           , QUOTE_DOUBLE,
			QUOTE_DOUBLE, "ted"           , QUOTE_DOUBLE,
			WHITESPACE,
			">>",
			"append",
			WHITESPACE,
			NULL
		}
	},
	// TEST: redirections only (pipes)
	{
		.input = "< in | << heredoc > out | >> append",
		.arg = (char *[]) {
			PIPE,
			PIPE,
			NULL
		},
		.redir = (char *[]) {
			"<",
			"in",
			WHITESPACE,
			PIPE,
			"<<",
			"heredoc",
			WHITESPACE,
			">",
			"out",
			WHITESPACE,
			PIPE,
			">>",
			"append",
			WHITESPACE,
			NULL
		}
	},
	// TEST: redirections only (compact)
	{
		.input = "<in<<heredoc>out>>append",
		.arg = (char *[]) {
			NULL
		},
		.redir = (char *[]) {
			"<",
			"in",
			WHITESPACE,
			"<<",
			"heredoc",
			WHITESPACE,
			">",
			"out",
			WHITESPACE,
			">>",
			"append",
			WHITESPACE,
			NULL
		}
	},
	// TEST: redirections only (pipes, compact)
	{
		.input = "<in|<<heredoc>out|>>append",
		.arg = (char *[]) {
			PIPE,
			PIPE,
			NULL
		},
		.redir = (char *[]) {
			"<",
			"in",
			WHITESPACE,
			PIPE,
			"<<",
			"heredoc",
			WHITESPACE,
			">",
			"out",
			WHITESPACE,
			PIPE,
			">>",
			"append",
			WHITESPACE,
			NULL
		}
	},
	// TEST: mixed arguments and redirections
	{
		.input = "cat -e << END < test.txt",
		.arg = (char *[]) {
			"cat",
			WHITESPACE,
			"-e",
			WHITESPACE,
			NULL
		},
		.redir = (char *[]) {
			"<<",
			"END",
			WHITESPACE,
			"<",
			"test.txt",
			WHITESPACE,
			NULL
		}
	},
	// TEST: mixed arguments and redirections (pipes)
	{
		.input = "cat -e << END | echo < test.txt | ls -l > out.txt",
		.arg = (char *[]) {
			"cat",
			WHITESPACE,
			"-e",
			WHITESPACE,
			PIPE,
			"echo",
			WHITESPACE,
			PIPE,
			"ls",
			WHITESPACE,
			"-l",
			WHITESPACE,
			NULL
		},
		.redir = (char *[]) {
			"<<",
			"END",
			WHITESPACE,
			PIPE,
			"<",
			"test.txt",
			WHITESPACE,
			PIPE,
			">",
			"out.txt",
			WHITESPACE,
			NULL
		}
	},
	// TEST: mixed arguments and redirections (compact)
	{
		.input = "cat -e<<END<test.txt",
		.arg = (char *[]) {
			"cat",
			WHITESPACE,
			"-e",
			NULL
		},
		.redir = (char *[]) {
			"<<",
			"END",
			WHITESPACE,
			"<",
			"test.txt",
			WHITESPACE,
			NULL
		}
	},
	// TEST: mixed arguments and redirections (pipes, compact)
	{
		.input = "cat -e<<END|echo<test.txt|ls -l>out.txt",
		.arg = (char *[]) {
			"cat",
			WHITESPACE,
			"-e",
			PIPE,
			"echo",
			PIPE,
			"ls",
			WHITESPACE,
			"-l",
			NULL
		},
		.redir = (char *[]) {
			"<<",
			"END",
			WHITESPACE,
			PIPE,
			"<",
			"test.txt",
			WHITESPACE,
			PIPE,
			">",
			"out.txt",
			WHITESPACE,
			NULL
		}
	},
};

TestSuite(tokenise, .timeout = 1);

ParameterizedTestParameters(tokenise, tokenise_test)
{
	size_t	nb_params;

	nb_params = sizeof(g_param) / sizeof(*g_param);
	return (cr_make_param_array(t_param, g_param, nb_params));
}

ParameterizedTest(
	t_param *param,
	tokenise,
	tokenise_test
) {
	t_data	data;
	int32_t	stdin_old;
	int32_t	stdin_new;
	int32_t	stdout_old;
	size_t	index;
	
	cr_assert_eq(stdin_redir(&stdin_old, &stdin_new), EXIT_SUCCESS);
	cr_assert_eq(stdin_send(param->input, stdin_new), EXIT_SUCCESS);
	stdout_old = stdout_disable();

	cr_assert_eq(state_parse(&data), EXIT_SUCCESS);
	cr_assert_eq(state_tokenise(&data), EXIT_SUCCESS);

	cr_assert_eq(stdin_reset(stdin_old, stdin_new), EXIT_SUCCESS);
	stdout_enable(stdout_old);

	index = 0;
	while (param->arg[index] != NULL)
	{
		cr_assert_str_eq(
			vptr_get(t_str, data.arg, index).get,
			param->arg[index]
		);
		index++;
	}
	if (param->arg[0] != NULL)
		cr_assert_eq(data.arg->len, index);

	index = 0;
	while (param->redir[index] != NULL)
	{
		cr_assert_str_eq(
			vptr_get(t_str, data.redir, index).get, param->redir[index],
			"redir='%d', expected='%d'\n",
			vptr_get(t_str, data.redir, index).get[0], param->redir[index][0]
		);
		index++;
	}
	if (param->redir[0] != NULL)
		cr_assert_eq(data.redir->len, index);

	vstr_destroy(data.arg);
	vstr_destroy(data.redir);
	vstr_destroy(data.user_input);
}
