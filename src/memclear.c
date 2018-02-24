#include <ftmalloc.h>

void					mem_clear_space(t_mcfg *dat, void *addr)
{
	t_area			*a;
	t_blk			*b;

	a = dat->areas;
	while (a)
	{
		b = a->blocks;
		while (b)
		{
			if (b->addr == addr)
			{
				b->freed = 1;
				b->allocsize = 0;
			}
			b = b->next;
		}
		a = a->next;
	}
}
