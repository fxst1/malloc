/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 18:45:30 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/03 18:39:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void			*malloc(size_t size)
{
	t_mcfg		*cfg;
	intptr_t	addr;
	size_t		typesize;

	addr = 0x0;
	cfg = mem_get_data();
	typesize = mem_get_typesize(size);
	mem_lock(cfg);
	if (mem_is_overlap(cfg))
		return (NULL);
	else if (size > 0 && !mem_size_overflow(cfg->psize, typesize))
	{
		ft_mem_delete(cfg, &cfg->areas);
		addr = mem_search_space(cfg, size, typesize);
		if (!addr)
			addr = ft_mem_new(cfg, size, typesize);
	}
	mem_unlock(cfg);
	return ((void*)addr);
}
