#include <ftmalloc.h>

static void			*reset_area(t_blk *b, void *addr, size_t size, int *find)
{
	while (b)
	{
		if (b->freed)
		{
			b->freed = 0;
			b->allocsize = size;
			return (b->addr);
		}
		if (b->addr == addr)
		{
			(*find) = 1;
			b->freed = 1;
			b->allocsize = 0;
		}
		b = b->next;
	}
	return (NULL);
}

static int			find_blk(t_blk *b, void *addr)
{
	while (b)
	{
		if (b->addr == addr)
		{
			b->freed = 1;
			b->allocsize = 0;
			return (1);
		}
		b = b->next;
	}
	return (0);
}

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

void				*mem_reset_space(t_mcfg *dat, void *addr, size_t size, size_t blktype)
{
	t_area			*a;
	void			*ret;
	void			*expected_addr;
	int				find;

	ret = NULL;
	find = 0;
	a = dat->areas;
	expected_addr = (void*)dat->areas;
	while (a)
	{
		if (a->blktype == blktype && !ret)
			ret = reset_area(a->blocks, addr, size, &find);
		else if (!find)
			find = find_blk(a->blocks, addr);
		if (ret && find)
			return (ret);
		if (expected_addr && (intptr_t)a >= (intptr_t)expected_addr)
			expected_addr = (void*)a + a->psize;
		a = a->next;
	}
	return (create_area(dat, size, expected_addr));
}
