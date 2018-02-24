/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:25:48 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 20:13:37 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void		show_area_header(t_area *a)
{
	if (a->blktype == FTMALLOC_TINY)
		write(STDOUT_FILENO, "TINY : ", 7);
	else if (a->blktype == FTMALLOC_SMALL)
		write(STDOUT_FILENO, "SMALL : ", 7);
	else
		write(STDOUT_FILENO, "BIG : ", 7);
	ft_printhex((intptr_t)a, -1, 1);
	write(STDOUT_FILENO, " (", 2);
	ft_printnum(a->nblk);
	write(STDOUT_FILENO, " blocks)\t", 9);
	ft_printnum(a->psize);
	write(STDOUT_FILENO, " bytes\n", 7);
}

static void		show_blocks(int flag, t_blk *b)
{
	if (!b->freed)
	{
		if (flag & FTMALLOC_SHOW_BLOCK)
		{
			ft_printhex((intptr_t)b, FTMALLOC_DBG_MAXDIGIT, 1);
			write(STDOUT_FILENO, " - ", 3);
			ft_printhex(((intptr_t)b) + b->allocsize + sizeof(t_blk),
				FTMALLOC_DBG_MAXDIGIT, 1);
			write(STDOUT_FILENO, ":\t", 2);
			ft_printnum(b->allocsize);
			write(STDOUT_FILENO, " bytes\n", 7);
		}
		if (flag & FTMALLOC_SHOW_CONTENT)
			ft_print_memory(b->addr, b->allocsize);
	}
	else if (flag & FTMALLOC_SHOW_FREE)
	{
		ft_printhex((intptr_t)b, FTMALLOC_DBG_MAXDIGIT, 1);
		write(STDOUT_FILENO, " - ", 3);
		ft_printhex((intptr_t)b + b->allocsize + sizeof(t_blk),
			FTMALLOC_DBG_MAXDIGIT, 1);
		write(STDOUT_FILENO, ":\t", 2);
		write(STDOUT_FILENO, "Unused block\n", 13);
	}
	b = b->next;
}

void			show_data(t_mcfg *dat, int flag)
{
	t_area			*a;
	t_blk			*b;

	a = dat->areas;
	while (a)
	{
		if (flag & FTMALLOC_SHOW_AREA)
			show_area_header(a);
		b = a->blocks;
		while (b)
		{
			show_blocks(flag, b);
		}
		a = a->next;
	}
}
