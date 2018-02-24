/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:22:16 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 18:13:07 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void	print_info_header(t_area *a)
{
	if (a->blktype == FTMALLOC_TINY)
		write(STDOUT_FILENO, "TINY : ", 7);
	else if (a->blktype == FTMALLOC_SMALL)
		write(STDOUT_FILENO, "SMALL : ", 7);
	else
		write(STDOUT_FILENO, "BIG : ", 7);
	ft_printhex(a->psize, -1, 1);
	write(STDOUT_FILENO, " (", 2);
	ft_printnum(a->nblk);
	write(STDOUT_FILENO, ")", 1);
	write(STDOUT_FILENO, "\n", 1);
}

static void	print_info(t_area *a)
{
	t_blk	*b;

	b = a->blocks;
	print_info_header(a);
	while (b)
	{
		ft_printhex((unsigned long)b->addr, FTMALLOC_DBG_MAXDIGIT, 1);
		write(STDOUT_FILENO, " - ", 3);
		ft_printhex((unsigned long)b->addr + b->allocsize,
			FTMALLOC_DBG_MAXDIGIT, 1);
		write(STDOUT_FILENO, " : ", 3);
		if (!b->freed)
		{
			ft_printnum(b->allocsize);
			write(STDOUT_FILENO, " bytes\n", 7);
		}
		else
			write(STDOUT_FILENO, "Unused block\n", 13);
		b = b->next;
	}
}

void		show_alloc(void)
{
	t_mcfg	*dat;
	t_area	*a;

	dat = mem_get_data();
	a = dat->areas;
	while (a)
	{
		print_info(a);
		a = a->next;
	}
}
