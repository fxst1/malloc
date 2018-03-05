/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 18:45:30 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/05 10:40:40 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void 		*malloc(size_t size)
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
//		ft_printstr("Malloc : ");
//		ft_printnum(size);
//		ft_printstr("\n");
		addr = mem_search_space(cfg, size, typesize);
		if (!addr)
			addr = mem_new(cfg, size, typesize);
	}
	else if (size)
		write(2, "Error: Overflow\n", 16);
	mem_unlock(cfg);
	return ((void*)addr);
}
