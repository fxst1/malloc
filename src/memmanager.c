/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmanager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:58:12 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 18:11:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void			mem_area_set_process(t_blk *blk,
						size_t allocsize, size_t i)
{
	blk->addr = (void*)((intptr_t)blk + sizeof(t_blk));
	if (i == 0)
	{
		blk->freed = 0;
		blk->allocsize = allocsize;
	}
	else
	{
		blk->freed = 1;
		blk->allocsize = 0;
	}
}

void				mem_area_set(t_area *a, size_t allocsize, size_t blksize,
						size_t mapsize)
{
	t_blk			*blk;
	size_t			i;

	a->blocks = (t_blk*)((intptr_t)a + sizeof(t_area));
	a->blktype = blksize;
	a->psize = mapsize;
	a->nblk = mem_get_nblk(a->blktype, a->psize);
	blk = a->blocks;
	i = 0;
	while (i < a->nblk)
	{
		mem_area_set_process(blk, allocsize, i);
		if (i + 1 < a->nblk)
			blk->next = (t_blk*)(((intptr_t)blk->addr) + a->blktype);
		else
			blk->next = NULL;
		blk = blk->next;
		i++;
	}
	a->next = NULL;
}

t_area				*mem_area_init(t_mcfg *dat, size_t psize,
						size_t allocsize, void *expected_addr)
{
	void			*start;
	size_t			i;
	size_t			mapsize;

	expected_addr = NULL;
	if (allocsize >= dat->psize * FTMALLOC_FACTOR)
	{
		i = allocsize;
		mapsize = (dat->psize * FTMALLOC_FACTOR) + sizeof(t_area)
					+ sizeof(t_blk) + allocsize;
	}
	else
	{
		i = mem_get_blksize(allocsize);
		mapsize = dat->psize * FTMALLOC_FACTOR;
	}
	start = mmap(expected_addr, mapsize, dat->opts.prot, dat->opts.flags,
				dat->opts.fd, dat->opts.offset);
	if (!start || start == MAP_FAILED)
		return (NULL);
	mem_area_set((t_area*)start, allocsize, i, mapsize);
	return ((t_area*)start);
	(void)psize;
}

static int			may_clear_blk(t_blk *b)
{
	while (b)
	{
		if (!b->freed)
			return (0);
		b = b->next;
	}
	return (1);
}

void				mem_areas_clear(t_area **dat)
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
			munmap((void*)a, a->psize);
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
