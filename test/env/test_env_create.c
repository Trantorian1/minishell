/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:36:36 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 17:49:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stddef.h>

#include "env_create.h"
#include "env_destroy.h"

TestSuite(env_create, .timeout = 1);

Test(env_create, env_create_simple)
{
	t_vptr		*env;
	t_env_pair	pair;

	env = env_create(
		(t_cstr []) {
			"VAR0=0",
			"VAR1=1",
			"VAR2=2",
			NULL
		}
	);
	cr_assert_not_null(env);
	cr_assert_eq(env->len, 3);

	pair = vptr_get(t_env_pair, env, 0);
	cr_assert_str_eq(pair.key.get, "VAR0");
	cr_assert_str_eq(pair.val.get, "0");

	pair = vptr_get(t_env_pair, env, 1);
	cr_assert_str_eq(pair.key.get, "VAR1");
	cr_assert_str_eq(pair.val.get, "1");

	pair = vptr_get(t_env_pair, env, 2);
	cr_assert_str_eq(pair.key.get, "VAR2");
	cr_assert_str_eq(pair.val.get, "2");

	env_destroy(env);
}
