/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_size_overflow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 13:10:01 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/04 16:40:12 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

int				mem_size_overflow(size_t psize, size_t typesize)
{
	size_t			maxsize;

	if (typesize >= SIZE_T_MAX - sizeof(t_blk))
		return (1);
	maxsize = sizeof(t_area) + (FTMALLOC_NBLOCKS * (typesize + sizeof(t_blk)));
	if (maxsize < typesize)
		return (1);
//	while (maxsize % psize)
//		maxsize++;
	return (maxsize < typesize);
	(void)psize;
}
