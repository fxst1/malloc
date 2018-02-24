/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memutil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:00:51 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 18:20:44 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

size_t		mem_get_nblk(size_t blksize, size_t psize)
{
	return ((psize - sizeof(t_area)) / (sizeof(t_blk) + blksize));
}

size_t		mem_correct_factor(size_t psize, size_t allocsize)
{
	size_t	f;

	f = FTMALLOC_FACTOR;
	allocsize += sizeof(t_blk) + sizeof(t_area);
	while (allocsize > (psize * f))
		f *= 2;
	return (f);
}

size_t		mem_get_blksize(size_t allocsize)
{
	size_t			blksize;

	if (allocsize <= FTMALLOC_TINY)
		blksize = FTMALLOC_TINY;
	else if (allocsize <= FTMALLOC_SMALL)
		blksize = FTMALLOC_SMALL;
	else
		blksize = allocsize + sizeof(t_blk) + sizeof(t_area);
	return (blksize);
}

size_t		mem_get_pagesize(size_t blksize)
{
	return (blksize * FTMALLOC_FACTOR);
}

void		mem_numofdigit(intptr_t v, unsigned int base, size_t *n)
{
	if (v >= base)
	{
		mem_numofdigit(v / base, base, n);
		mem_numofdigit(v % base, base, n);
	}
	else
	{
		(*n)++;
	}
}
