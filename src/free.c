/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 18:45:30 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/09 15:15:17 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void		get_area_and_free_block(t_area *a, intptr_t addr)
{
	t_blk		*b;

	while (a)
	{
		b = a->blocks;
		while (b)
		{
			if (b->addr == addr)
			{
				b->allocsize = 0;
				b->freed = 1;
				return ;
			}
			b = b->next;
		}
		a = a->next;
	}
}

void			free(void *addr)
{
	t_mcfg		*cfg;

	cfg = mem_get_data();
	mem_lock(cfg);
	get_area_and_free_block(cfg->areas, (intptr_t)addr);
	ft_mem_delete(cfg, &cfg->areas);
	mem_unlock(cfg);
}
