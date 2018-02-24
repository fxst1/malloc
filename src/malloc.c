#include <ftmalloc.h>

void				*malloc(size_t size)
{
	void			*ret;
	t_mcfg			*dat;

	if (!size || size > SIZE_T_MAX - sizeof(t_area) - sizeof(t_blk))
		return (NULL);
	dat = mem_get_data();
	mem_lock(dat);
	ret = mem_get_free_space(dat, size, mem_get_blksize(size));
	if (dat->malloc_hook)
		dat->malloc_hook(size, (const void*(*))malloc);
	mem_unlock(dat);
	return (ret);
}

void				*calloc(size_t nmenb, size_t size)
{
	return (malloc(nmenb * size));
}

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

int					alloc_dump(const int fd, const void *addr)
{
	t_mcfg			*dat;
	t_area			*a;
	t_blk			*b;

	dat = mem_get_data();
	mem_lock(dat);
	a = dat->areas;
	while (a)
	{
		b = a->blocks;
		while (b)
		{
			if (addr == b->addr)
			{
				if (!b->freed)
					return (-1);
				write(fd, "FT", 2);
				write(fd, &b->allocsize, sizeof(b->allocsize));
				write(fd, addr, b->allocsize);
				return (b->allocsize);
			}
			b = b->next;
		}
		a = a->next;
	}
	mem_unlock(dat);
	return (-1);
}

ssize_t				alloc_readdump(int const fd, void **addr)
{
	char			c[2];
	size_t			size;

	if (!addr)
		return (-1);
	if (read(fd, &c, 2) != 2)
		return (-1);
	else if (c[0] != 'F' || c[1] != 'T')
		return (-1);
	else if (read(fd, &size, sizeof(size)) != sizeof(size))
		return (-1);
	*addr = realloc(*addr, size);
	if (*addr)
		read(fd, *addr, size);
	return (size);
}
