/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 13:10:05 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/06 09:08:24 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static intptr_t	can_realloc_same(t_area *a, intptr_t addr, size_t allocsize, size_t typesize)
{
	t_blk		*b;

	while (a)
	{
		b = a->blocks;
		while (b)
		{
			if (b->addr == addr)
			{
				if (typesize == a->blksize)
				{
					b->allocsize = allocsize;
					return (b->addr);
				}
				b->allocsize = 0;
				b->freed = 1;
				return (0x0);
			}
			b = b->next;
		}
		a = a->next;
	}
	return (0x0);
}

void 			*realloc(void *addr, size_t size)
{
	t_mcfg		*cfg;
	intptr_t	ptr;
	size_t		typesize;

	ft_printstr("Realloc\n");
	ptr = 0x0;
	cfg = mem_get_data();
	mem_lock(cfg);
	typesize = mem_get_typesize(size);
	if (addr && (ptr = can_realloc_same(cfg->areas, (intptr_t)addr, size, typesize)))
	{
		mem_delete(cfg, &cfg->areas);
		mem_unlock(cfg);
		return (addr);
	}
	else if (size > 0 && !mem_size_overflow(cfg->psize, typesize) && !mem_is_overlap(cfg))
	{
		ptr = mem_search_space(cfg, size, typesize);
		if (!ptr)
			ptr = mem_new(cfg, size, typesize);
	}
	mem_unlock(cfg);
	if (!ptr)
	{
		errno = ENOMEM;
		ft_printstr("\tERROR\n");
	}
	return ((void*)ptr);
}
