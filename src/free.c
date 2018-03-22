/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 18:45:30 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/22 08:35:29 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void		get_area_and_free_block(t_area *a, intptr_t addr)
{
	t_blk		*b;
	size_t		i;

	while (a)
	{
		i = 0;
		b = a->blocks;
		while (i < FTMALLOC_NBLOCKS)
		{
			if (b->addr == addr)
			{
				b->freed = 1;
				return;
			}
			b = (t_blk*)(((intptr_t)b) + sizeof(t_blk) + a->blksize);
			i++;
		}
		a = a->next;
	}
}

void 				free(void *addr)
{
	t_mcfg		*cfg;

//	ft_printstr("Free\n");
	cfg = mem_get_data();
	mem_lock(cfg);
	if (!mem_is_overlap(cfg))
	{
		get_area_and_free_block(cfg->areas, (intptr_t)addr);
		ft_mem_delete(cfg, &cfg->areas);
	}
	mem_unlock(cfg);
	//show_alloc_mem();
}
