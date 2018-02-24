/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memfreespace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:26:24 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 18:12:36 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void			*create_area(t_mcfg *dat, size_t size, void *expected_addr)
{
	t_area			*a;

	if ((a = mem_area_init(dat, dat->psize, size, expected_addr)))
	{
		a->next = dat->areas;
		dat->areas = a;
		return (a->blocks->addr);
	}
	return (NULL);
}

static void			*look_for_space(t_blk *b, size_t size)
{
	while (b)
	{
		if (b->freed)
		{
			b->freed = 0;
			b->allocsize = size;
			return (b->addr);
		}
		b = b->next;
	}
	return (NULL);
}

void				*mem_get_free_space(t_mcfg *dat, size_t size,
						size_t blktype)
{
	t_area			*a;
	void			*expected_addr;
	void			*tmp;

	a = dat->areas;
	expected_addr = (void*)dat->areas;
	while (a)
	{
		if (a->blktype == blktype)
		{
			tmp = look_for_space(a->blocks, size);
			if (tmp)
				return (tmp);
		}
		if (expected_addr && (intptr_t)expected_addr < (intptr_t)a)
			expected_addr = (void*)((intptr_t)a) + a->psize;
		a = a->next;
	}
	return (create_area(dat, size, expected_addr));
}
