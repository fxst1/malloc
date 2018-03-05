/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 11:39:27 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/05 11:36:22 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void			create_blocks(t_blk *b, size_t blksize, intptr_t end)
{
	size_t			i;

	i = 0;
	while (i <= FTMALLOC_NBLOCKS && ((intptr_t)b) < end)
	{
		b->allocsize = 0;
		b->freed = 1;
		b->addr = (intptr_t)b + sizeof(t_blk);
		if (i + 1 <= FTMALLOC_NBLOCKS &&
			((intptr_t)(b->addr + blksize)) < end)
		{
			b->next = (t_blk*)(b->addr + blksize);
			b = b->next;
			i++;
		}
		b->next = NULL;
		break ;
	}
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
		a->prev = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		a->prev = tmp;
		tmp->next = a;
	}
}
/*
static t_area		*get_aligned_map(t_mcfg *cfg, size_t total_size)
{
	t_area			*a;
	t_area			*align;
	intptr_t		n;

	a = (t_area*)mmap(NULL, 2 * total_size, cfg->opts.prot, cfg->opts.flags, cfg->opts.fd, 0);
	if (a == NULL || a == MAP_FAILED)
		return (NULL);
	align = a;
	n = (intptr_t)a;
	align = (t_area*)((((n) + (total_size) - 1) / (total_size)) * (total_size));
	if (align != a)
		munmap(a, align - a);
	munmap(a + total_size, total_size - (align - a));
	return (mmap(align, total_size, cfg->opts.prot, cfg->opts.flags | MAP_FIXED, cfg->opts.fd, 0));
}*/

intptr_t			mem_new(t_mcfg *cfg, size_t allocsize, size_t typesize)
{
	t_area			*a;
	size_t			total_size;

	total_size = real_alloc_size(cfg->psize, typesize);
	ft_printstr("Mapping : ");
	ft_printnum(total_size);
	ft_printstr("\n");
	a = (t_area*)mmap((void*)cfg->expected, total_size, cfg->opts.prot, cfg->opts.flags,
		cfg->opts.fd, 0);
	//a = get_aligned_map(cfg, total_size);
	if (a == NULL || ((void*)a) == MAP_FAILED)
	{
		write(STDERR_FILENO, "FAIL\n", 5);
		return (0x0);
	}
	a->total_size = total_size;
	a->blksize = typesize;
	a->next = NULL;
	a->blocks = (t_blk*)((intptr_t)a + sizeof(t_area));
	append_area(cfg, a);
	create_blocks(a->blocks, typesize, (intptr_t)(a + total_size));
	mem_get_total(typesize, 1);
	a->blocks->allocsize = allocsize;
	a->blocks->freed = 0;
	return (a->blocks->addr);
}
