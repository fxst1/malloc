/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 11:39:27 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/06 09:54:34 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void			create_blocks(t_blk *b, size_t blksize, intptr_t end)
{
	size_t			i;

	i = 0;
	while (i <= FTMALLOC_NBLOCKS /*&& ((intptr_t)b) < end*/)
	{
		b->allocsize = 0;
		b->freed = 1;
		b->addr = (intptr_t)b + sizeof(t_blk);
		if (i + 1 <= FTMALLOC_NBLOCKS /* &&
			((intptr_t)(b->addr + blksize)) < end*/)
		{
			b->next = (t_blk*)(b->addr + blksize);
			b = b->next;
		}
		else
			b->next = NULL;
		i++;
	}
	(void)end;
}

static size_t		real_alloc_size(size_t psize, size_t typesize)
{
	size_t			rsize;

	rsize = sizeof(t_area) + (FTMALLOC_NBLOCKS * (typesize + sizeof(t_blk)));
	while (rsize % psize)
		rsize++;
	return (rsize);
}

static void			append_area(t_mcfg *cfg, t_area *a)
{
	t_area			*tmp;

	tmp = cfg->areas;
	if (tmp == NULL)
	{
		cfg->areas = a;
	//	a->prev = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		//a->prev = tmp;
		tmp->next = a;
	}
}
/*
static t_area		*get_aligned_map(t_mcfg *cfg, size_t total_size)
{
	void			*align;
	intptr_t		n;

	align = mmap(NULL, total_size,
				cfg->opts.prot, cfg->opts.flags, cfg->opts.fd, 0);
	if (align == NULL || align == MAP_FAILED)
		return (NULL);
	n = (intptr_t)align;
	while ((n & 0xF) != 0)
		n++;
	munmap(align, total_size);
	return (mmap((void*)n, total_size,
				cfg->opts.prot, cfg->opts.flags, cfg->opts.fd, 0));
}

static size_t		get_aligned_offset(void **addr, size_t typesize)
{
	while (((intptr_t)(*addr) & 0xF) != 0)
	{
		typesize--;
		(*addr)++;
	}
	return (typesize);
}
*/
intptr_t			mem_new(t_mcfg *cfg, size_t allocsize, size_t typesize)
{
	t_area			*a;
	size_t			total_size;

	total_size = real_alloc_size(cfg->psize, typesize);
	ft_printstr("Mapping : ");
	ft_printnum(total_size);
	a = (t_area*)mmap(NULL, total_size, cfg->opts.prot, cfg->opts.flags,
		cfg->opts.fd, 0);
	if (a == NULL || ((void*)a) == MAP_FAILED)
	{
		write(STDERR_FILENO, "FAIL\n", 5);
		return (0x0);
	}
	ft_printshl(" => ", (intptr_t)a);
	a->blocks = (t_blk*)((intptr_t)a + sizeof(t_area));
	a->total_size = total_size;
	a->blksize = typesize;
	a->next = NULL;
	append_area(cfg, a);
	create_blocks(a->blocks, typesize, (intptr_t)(a + total_size));
	a->blocks->allocsize = allocsize;
	a->blocks->freed = 0;
//	ft_printshl(" => ", (intptr_t)a->blocks);
	return (a->blocks->addr);
}
