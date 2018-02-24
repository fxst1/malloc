/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memusage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:58:12 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 18:21:13 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

size_t			mem_get_unused(t_area *a)
{
	size_t			unusage;
	int				clear;
	t_blk			*b;

	unusage = 0;
	while (a)
	{
		clear = 1;
		b = a->blocks;
		while (b)
		{
			if (!b->freed)
			{
				clear = 0;
				unusage += (a->blktype - b->allocsize);
			}
			b = b->next;
		}
		if (clear)
			unusage += a->psize;
		a = a->next;
	}
	return (unusage);
}

size_t			mem_get_usage(t_area *a)
{
	size_t			usage;
	t_blk			*b;

	usage = 0;
	while (a)
	{
		b = a->blocks;
		while (b)
		{
			if (!b->freed)
				usage += b->allocsize;
			b = b->next;
		}
		a = a->next;
	}
	return (usage);
}

size_t			mem_get_page_usage(t_area *a)
{
	size_t			usage;

	usage = 0;
	while (a)
	{
		usage += a->psize;
		a = a->next;
	}
	return (usage);
}

size_t			mem_get_block_usage(t_area *a)
{
	size_t			usage;
	t_blk			*b;

	usage = 0;
	while (a)
	{
		b = a->blocks;
		while (b)
		{
			if (!b->freed)
				usage += a->blktype;
			b = b->next;
		}
		a = a->next;
	}
	return (usage);
}
