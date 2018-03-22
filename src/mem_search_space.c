/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_search_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 11:30:10 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/22 14:59:52 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

t_blk		*research_into_mem(t_area *a)
{
	t_blk	*b;
	size_t	i;

	i = 0;
	b = a->blocks;
	while (i < FTMALLOC_NBLOCKS)
	{
		if (b->freed)
			return (b);
		b = (t_blk*)(((intptr_t)b) + sizeof(t_blk) + a->blksize);
		i++;
	}
	return (NULL);
}

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
		if ((b = research_into_mem(a)))
		{
			b->freed = 0;
			return (b->addr);
		}
		a = a->next;
	}
	return (0x0);
	(void)allocsize;
}
