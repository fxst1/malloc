/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:53:11 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/22 08:36:12 by fxst1            ###   ########.fr       */
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

static void		block_view(t_blk *b, size_t *total, size_t blksize)
{
	size_t		i;

	i = 0;
	while (i < FTMALLOC_NBLOCKS)
	{
		ft_printaddr(b->addr);
		write(STDOUT_FILENO, " - ", 3);
		ft_printaddr((intptr_t)b + blksize + sizeof(t_blk));
		write(STDOUT_FILENO, " : ", 3);
		ft_printnum(blksize);
		if (!b->freed)
		{
			if (blksize == 1)
				write(STDOUT_FILENO, " octet", 6);
			else
				write(STDOUT_FILENO, " octets", 6);
			*total += blksize;
		}
		else
			write(STDOUT_FILENO, " (freed)", 8);
		write(STDOUT_FILENO, "\n", 1);
		b = (t_blk*)(((intptr_t)b) + sizeof(t_blk) + blksize);
		i++;
	}
}

void 			show_alloc_mem(void)
{
	t_mcfg		*cfg;
	t_area		*a;
	size_t		total;

	cfg = mem_get_data();
	mem_lock(cfg);
	total = 0;
	if (!mem_is_overlap(cfg))
	{
		a = cfg->areas;
		while (a)
		{
			area_header(a);
			block_view(a->blocks, &total, a->blksize);
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
