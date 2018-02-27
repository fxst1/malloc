/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:51:24 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/27 19:04:22 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>
#include <unistd.h>

void				*malloc(size_t size)
{
	void			*ret;
	t_mcfg			*dat;

	write(1, "Malloc\n", 7);
	if (!size /*|| size > SIZE_T_MAX - sizeof(t_area) - sizeof(t_blk)*/)
		return (NULL);
	dat = mem_get_data();
	mem_lock(dat);
	ret = mem_get_free_space(dat, size, mem_get_blksize(size));
	if (dat->malloc_hook)
		dat->malloc_hook(size, (const void*(*))malloc);
	mem_unlock(dat);
	//show_alloc();
	return (ret);
}

void				*calloc(size_t nmenb, size_t size)
{
	write(1, "Calloc\n", 7);
	return (malloc(nmenb * size));
}

void				free(void *addr)
{
	t_mcfg			*dat;

	if (addr)
	{
		dat = mem_get_data();
		mem_lock(dat);
		mem_clear_space(dat, addr);
		mem_areas_clear(&dat->areas);
		mem_unlock(dat);
	}
}

int					mallopt(int param, int value)
{
	t_mcfg			*dat;

	dat = mem_get_data();
	mem_lock(dat);
	if (param == M_ARENA_MAX && value >= 0)
		dat->arenamax = value;
	else
	{
		mem_unlock(dat);
		return (0);
	}
	mem_unlock(dat);
	return (1);
}

void				*malloc_spec(size_t size, t_alloc_opts *opts)
{
	void			*ret;
	t_mcfg			*dat;
	t_alloc_opts	backopts;

	if (!opts)
		return (malloc(size));
	dat = mem_get_data();
	mem_lock(dat);
	backopts = dat->opts;
	dat->opts = *opts;
	ret = mem_get_free_space(dat, size, mem_get_blksize(size));
	if (dat->malloc_hook)
		dat->malloc_hook(size, (const void*(*))malloc);
	dat->opts = backopts;
	mem_unlock(dat);
	return (ret);
}
