/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:49:34 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 16:24:09 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void				*realloc(void *addr, size_t size)
{
	void			*ret;
	t_mcfg			*dat;

	if (!size || size > SIZE_T_MAX - sizeof(t_area) - sizeof(t_blk))
		return (NULL);
	else if (!addr)
		return (malloc(size));
	dat = mem_get_data();
	mem_lock(dat);
	mem_areas_clear(&dat->areas);
	ret = mem_reset_space(dat, addr, size, mem_get_blksize(size));
	if (dat->realloc_hook)
		dat->realloc_hook(size, (const void*(*))realloc);
	mem_unlock(dat);
	return (ret);
	(void)size;
}

void				*reallocarray(void *ptr, size_t nmenb, size_t size)
{
	return (realloc(ptr, nmenb * size));
}
