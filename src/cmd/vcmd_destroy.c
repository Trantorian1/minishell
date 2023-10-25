/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vcmd_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:48:45 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 17:51:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vcmd_destroy.h"

#include <stddef.h>

#include "dynamic/vector.h"
#include "dynamic/alloc.h"
#include "s_cmd.h"

void	vcmd_destroy(t_vptr *_Nullable vcmd)
{
	size_t	index;
	t_cmd	cmd;

	if (vcmd == NULL)
		return ;

	index = 0;
	while (index < vcmd->len)
	{
		cmd = vptr_get(t_cmd, vcmd, index);
		safe_free(cmd.arg);
		safe_free(cmd.redir);

		index++;
	}

	vptr_destroy(vcmd);
}
