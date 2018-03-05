/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_search_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 11:30:10 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/04 20:06:02 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

intptr_t 	mem_search_space(t_mcfg *dat, size_t allocsize, size_t typesize)
{
	t_area	*a;
	t_blk	*b;

	a = dat->areas;
	while (a)
	{
		if (a->blksize != typesize)
		{
			a = a->next;
			continue ;
		}
		b = a->blocks;
		while (b && !b->freed)
			b = b->next;
		if (b)
		{
			b->freed = 0;
			b->allocsize = allocsize;
			return (b->addr);
		}
		a = a->next;
	}
	return (0x0);
}
