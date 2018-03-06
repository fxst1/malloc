/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 13:21:53 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/06 09:47:41 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static int			may_clear_blk(t_blk *b)
{
	while (b)
	{
		if (b->allocsize > 0)
		{
		//	ft_printshl("Unclear block: ", (intptr_t)b);
			return (0);
		}
		b = b->next;
	}
	return (1);
}

void				mem_delete(t_mcfg *cfg, t_area **dat)
{
	t_area			*a;
	t_area			*last_a;
	t_area			*tmp;

	a = *dat;
	last_a = NULL;
	while (a)
	{
		if (may_clear_blk(a->blocks))
		{
			tmp = a->next;
			if ((void*)cfg->expected > (void*)a)
				cfg->expected = (intptr_t)a;
			//ft_printshl("Unmapping : ", (intptr_t)a);
			munmap((void*)a, a->total_size);
			if (last_a)
				last_a->next = tmp;
			else
				*dat = tmp;
			a = tmp;
		}
		else
		{
			last_a = a;
			a = a->next;
		}
	}
}
