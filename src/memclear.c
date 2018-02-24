/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:58:12 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 16:24:23 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void					mem_clear_space(t_mcfg *dat, void *addr)
{
	t_area			*a;
	t_blk			*b;

	a = dat->areas;
	while (a)
	{
		b = a->blocks;
		while (b)
		{
			if (b->addr == addr)
			{
				b->freed = 1;
				b->allocsize = 0;
			}
			b = b->next;
		}
		a = a->next;
	}
}
