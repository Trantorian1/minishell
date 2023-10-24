/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:57:52 by marvin            #+#    #+#             */
/*   Updated: 2023/10/24 18:21:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stddef.h>

#include "env_create.h"
#include "env_destroy.h"
#include "env_get.h"
#include "env_update.h"

TestSuite(env_update, .timeout = 1);

Test(env_update, env_update_simple)
{
	t_vptr	*env;

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

	cr_assert_not_null(env_update(env, "VAR1=42"));
	cr_assert_str_eq(env_get(env, "VAR1").get, "42");

	env_destroy(env);
}
