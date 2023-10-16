/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 08:18:09 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 11:46:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdio.h>

#include "dynamic/vector.h"
#include "dynamic/string.h"

TestSuite(build, .timeout = 1);

Test(build, build_dummy)
{
	t_vptr	*vptr;

	vptr = vptr_create(t_str, 0);
	vptr_destroy(vptr);

	printf("build system intact\n");
}
