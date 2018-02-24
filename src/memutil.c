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

void		mem_printnum(intptr_t v)
{
	if (v >= 10)
	{
		mem_printnum(v / 10);
		mem_printnum(v % 10);
	}
	else
	{
		v = (v <= 9 ? v + '0' : v - 10 + 'A');
		write(1, &v, 1);
	}
}

static void		mem_printaddr2(intptr_t v, size_t *n)
{
	if (v >= 16)
	{
		mem_printaddr2(v / 16, n);
		mem_printaddr2(v % 16, n);
	}
	else
	{
		(*n)++;
		v = (v <= 9 ? v + '0' : v - 10 + 'A');
		write(1, &v, 1);
	}
}

void		mem_printaddr(intptr_t v, int max, int show_x)
{
	size_t	n;

	n = 0;
	if (!v)
	{
		if (show_x)
			write(1, "0x0", 3);
	}
	else
	{
		if (show_x)
			write(1, "0x", 2);
		mem_printaddr2((unsigned long)v, &n);
		if (max > 0)
			while (n < (size_t)max)
			{
				write(1, "0", 1);
				n++;
			}
	}
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
