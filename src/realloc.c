/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 13:10:05 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/22 08:33:34 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static t_blk	*get_block(t_area *a, intptr_t addr, size_t *sizes, size_t size)
{
	t_blk		*b;
	size_t		i;

	sizes[0] = 0;
	sizes[1] = size;
	while (a)
	{
		b = a->blocks;
		i = 0;
		while (i < FTMALLOC_NBLOCKS)
		{
			if (b->addr == addr)
			{
				sizes[0] = a->blksize;
				return (b);
			}
			b = (t_blk*)(((intptr_t)b) + sizeof(t_blk) + a->blksize);
			i++;
		}
		a = a->next;
	}
	return (NULL);
}

static intptr_t	realloc_block(t_mcfg *cfg, t_blk *b, size_t *sizes, size_t typesize)
{
	size_t		min;
	intptr_t	ret;
	intptr_t	swap;

	b->freed = 1;
	swap = b->addr;
	min = (sizes[0] < typesize) ? sizes[0] : typesize;
	ret = mem_search_space(cfg, sizes[1], typesize);
	if (!ret)
		ret = ft_mem_new(cfg, sizes[1], typesize);
	if (ret)
		ft_memcpy((void*)ret, (const void*)swap, min);
	return (ret);
}

void 			*realloc(void *addr, size_t size)
{
	t_mcfg		*cfg;
	intptr_t	ret;
	t_blk		*b;
	size_t		typesize;
	size_t		sizes[2];

	ret = 0x0;
	cfg = mem_get_data();
	mem_lock(cfg);
	typesize = mem_get_typesize(size);
	b = get_block(cfg->areas, (intptr_t)addr, sizes, size);
	if (!b)
	{
		ft_mem_delete(cfg, &cfg->areas);
		ret = mem_search_space(cfg, size, typesize);
		if (!ret)
			ret = ft_mem_new(cfg, size, typesize);
		mem_unlock(cfg);
		return ((void*)ret);
	}
	else
		ret = realloc_block(cfg, b, sizes, typesize);
	mem_unlock(cfg);
	return ((void*)ret);
}
