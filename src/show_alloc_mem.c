/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:53:11 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/05 10:08:42 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void		area_header(t_area *a)
{
	ft_printaddr((intptr_t)a);
	write(STDOUT_FILENO, "\n", 1);
	if (a->blksize <= FTMALLOC_TINY)
		write(STDOUT_FILENO, "TINY : ", 7);
	else if (a->blksize <= FTMALLOC_SMALL)
		write(STDOUT_FILENO, "SMALL : ", 8);
	else
		write(STDOUT_FILENO, "BIG : ", 6);
	ft_printaddr((intptr_t)a);
	write(STDOUT_FILENO, "\n", 1);
}

static void		block_view(t_blk *b)
{
	while (b)
	{
		if (b->allocsize > 0)
		{
			ft_printaddr(b->addr);
			write(STDOUT_FILENO, " - ", 3);
			ft_printaddr(b->addr + b->allocsize);
			write(STDOUT_FILENO, " : ", 3);
			ft_printnum(b->allocsize);
			if (b->allocsize == 1)
				write(STDOUT_FILENO, " octet\n", 7);
			else if (b->allocsize > 0)
				write(STDOUT_FILENO, " octets\n", 8);
			else
				write(STDOUT_FILENO, "\n", 1);
		}
		//else
		//	write(STDOUT_FILENO, " empty\n", 7);
		b = b->next;
	}
}

void 			show_alloc_mem(void)
{
	t_mcfg		*cfg;
	t_area		*a;
	size_t		total;

	cfg = mem_get_data();
	mem_lock(cfg);
	if (mem_is_overlap(cfg))
	{
		total = mem_get_total(0, 0);
		a = cfg->areas;
		while (a)
		{
			area_header(a);
			block_view(a->blocks);
			a = a->next;
		}
		write(STDOUT_FILENO, "Total : ", 8);
		ft_printnum(total);
		if (total <= 1)
			write(STDOUT_FILENO, " octet\n", 7);
		else
			write(STDOUT_FILENO, " octets\n", 8);		
	}
	mem_unlock(cfg);
}
