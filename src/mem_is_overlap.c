/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_is_overlap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 09:16:13 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/05 11:19:21 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>
/*
static int	block_is_overlap(t_blk *b, size_t blksize)
{
	intptr_t	next;

	next = (intptr_t)(b + blksize + sizeof(t_blk));
	while (b)
	{
		if (next != (intptr_t)b->next)
			return (1);
		next = (intptr_t)(b + blksize + sizeof(t_blk));
		b = b->next;
	}
	return (0);
}
*/
int 		mem_is_overlap(t_mcfg *cfg)
{
	/*t_area		*a;
	intptr_t	tmp;
	intptr_t	next;

	a = cfg->areas;
	if (!a)
		return (0);
	tmp = (intptr_t)a;
	next = (tmp + a->total_size);
	while (a)
	{
		ft_printshl("AREA      : ", (intptr_t)a);
		ft_printshl("SIZE      : ", (intptr_t)a->total_size);
		ft_printshl("AREA NEXT : ", (intptr_t)a->next);
		ft_printshl("NEXT      : ", (intptr_t)next);
		ft_printshl("NEXT ADDR : ", (intptr_t)&a->next);
		ft_printstr("============================\n");
		if (a->next && next != (intptr_t)a->next)
		{
			write(STDERR_FILENO, "Overlap detected\n", 17);
			return (1);
		}
		tmp = (intptr_t)a;
		next = (tmp + a->total_size);
		a = a->next;
	}*/
	return (0);
	(void)cfg;
}
