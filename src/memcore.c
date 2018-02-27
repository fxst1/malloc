/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:58:09 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/27 19:09:24 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

#ifdef NO_MT_SAFE

static t_mcfg					init_mcfg(void)
{
	t_mcfg						dat;

	dat.psize = (size_t)getpagesize();
	dat.areas = NULL;
	dat.arenamax = 0;
	dat.malloc_hook = NULL;
	dat.realloc_hook = NULL;
	dat.free_hook = NULL;
	dat.opts.prot = PROT_READ | PROT_WRITE;
	dat.opts.flags = MAP_PRIVATE | MAP_ANON;
	dat.opts.fd = -1;
	dat.opts.offset = 0;
	return (dat);
}

#else

static t_mcfg					init_mcfg(void)
{
	static pthread_mutex_t		lock = PTHREAD_MUTEX_INITIALIZER;
	t_mcfg						dat;

	dat.psize = (size_t)getpagesize();
	dat.areas = NULL;
	dat.arenamax = 0;
	dat.malloc_hook = NULL;
	dat.realloc_hook = NULL;
	dat.free_hook = NULL;
	dat.lock = lock;
	dat.opts.prot = PROT_READ | PROT_WRITE | PROT_EXEC;
	dat.opts.flags = MAP_PRIVATE | MAP_ANONYMOUS;
	dat.opts.fd = -1;
	dat.opts.offset = 0;
	return (dat);
}

#endif

t_mcfg							*mem_get_data(void)
{
	static int					exist = 0;
	static t_mcfg				cfg;

	if (!exist)
	{
		cfg = init_mcfg();
		exist = 1;
	}
	return (&cfg);
}
