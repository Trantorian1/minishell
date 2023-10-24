/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:49:26 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 17:55:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stddef.h>

#include "dynamic/string.h"
#include "env_create.h"
#include "env_destroy.h"
#include "env_get.h"

TestSuite(env_get, .timeout = 1);

Test(env_get, env_get_simple)
{
	t_vptr	*env;
	t_str	val;

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

	val = env_get(env, "VAR0");
	cr_assert_str_eq(val.get, "0");

	val = env_get(env, "VAR1");
	cr_assert_str_eq(val.get, "1");

	val = env_get(env, "VAR2");
	cr_assert_str_eq(val.get, "2");

	val = env_get(env, "VAR3");
	cr_assert_str_eq(val.get, "");

	env_destroy(env);
}
