#include <ftmalloc.h>

static void		ft_printdouble(double d, unsigned int precision)
{
	int			dec;
	int			fl;
	size_t		i;

	i = 0;
	dec = (int)d;
	d -= dec;
	d *= precision;
	while (i < precision)
	{
		d *= 10;
		i++;
	}
	fl = (int)d;
	if (dec < 0)
	{
		dec = -dec;
		write(STDOUT_FILENO, "-", 1);
	}
	mem_printnum(dec);
	write(STDOUT_FILENO, ",", 1);
	mem_printnum(fl);
}

static void		show_waste(t_mcfg *dat)
{
	size_t		used;
	size_t		unused;

	used = mem_get_page_usage(dat->areas);
	unused = mem_get_unused(dat->areas);
	write(STDOUT_FILENO, "used:\t", 7);
	mem_printnum(used);
	write(STDOUT_FILENO, " bytes\n", 7);
	write(STDOUT_FILENO, "unused:\t", 8);
	mem_printnum(unused);
	write(STDOUT_FILENO, " bytes\n", 7);
	write(STDOUT_FILENO, "waste:\t", 7);
	ft_printdouble(used == 0 ? 0 : (unused * 100) / used, 2);
	write(STDOUT_FILENO, "%\n", 2);
}

static void		show_res(struct rusage u, int flag)
{
	write(STDOUT_FILENO, "Ressources: ", 12);
	write(STDOUT_FILENO, "\n", 1);
	if (flag & FTMALLOC_SHOW_RES_HARDPAGE)
	{
		write(STDOUT_FILENO, "\thard page faults: ", 19);
		mem_printnum(u.ru_majflt);
		write(STDOUT_FILENO, "\n", 1);
	}
	if (flag & FTMALLOC_SHOW_RES_SOFTPAGE)
	{
		write(STDOUT_FILENO, "\tsoft page faults: ", 19);
		mem_printnum(u.ru_minflt);
		write(STDOUT_FILENO, "\n", 1);
	}
}

static void		show_data(t_mcfg *dat, int flag)
{
	t_area			*a;
	t_blk			*b;

	a = dat->areas;
	while (a)
	{
		if (flag & FTMALLOC_SHOW_AREA)
		{
			if (a->blktype == FTMALLOC_TINY)
				write(STDOUT_FILENO, "TINY : ", 7);
			else if (a->blktype == FTMALLOC_SMALL)
				write(STDOUT_FILENO, "SMALL : ", 7);
			else
				write(STDOUT_FILENO, "BIG : ", 7);
			mem_printaddr((intptr_t)a, -1, 1);
			write(STDOUT_FILENO, " (", 2);
//			mem_printnum(a->psize);
			mem_printnum(a->nblk);
			write(STDOUT_FILENO, " blocks)\t", 9);
			mem_printnum(a->psize);
			write(STDOUT_FILENO, " bytes\n", 7);
		}
		b = a->blocks;
		while (b)
		{
			if (!b->freed)
			{
				if (flag & FTMALLOC_SHOW_BLOCK)
				{
					mem_printaddr((intptr_t)b, FTMALLOC_DBG_MAXDIGIT, 1);
					write(STDOUT_FILENO, " - ", 3);
					mem_printaddr(((intptr_t)b) + b->allocsize + sizeof(t_blk), FTMALLOC_DBG_MAXDIGIT, 1);
					write(STDOUT_FILENO, ":\t", 2);
					mem_printnum(b->allocsize);
					write(STDOUT_FILENO, " bytes\n", 7);
				}
				if (flag & FTMALLOC_SHOW_CONTENT)
					ft_print_memory(b->addr, b->allocsize);
			}
			else if (flag & FTMALLOC_SHOW_FREE)
			{
				mem_printaddr((intptr_t)b, FTMALLOC_DBG_MAXDIGIT, 1);
				write(STDOUT_FILENO, " - ", 3);
				mem_printaddr((intptr_t)b + b->allocsize + sizeof(t_blk), FTMALLOC_DBG_MAXDIGIT, 1);
				write(STDOUT_FILENO, ":\t", 2);
				write(STDOUT_FILENO, "Unused block\n", 13);
			}
			b = b->next;
		}
		a = a->next;
	}
}

void			show_alloc_dbg(unsigned int flag, int who)
{
	t_mcfg			*dat;
	struct rusage	u;

	dat = mem_get_data();
	mem_lock(dat);
	if (flag & FTMALLOC_SHOW_WASTE || flag & FTMALLOC_SHOW_RES)
	{
		if (flag & FTMALLOC_SHOW_WASTE)
			show_waste(dat);
		if (flag & FTMALLOC_SHOW_RES)
		{
			getrusage(who, &u);
			show_res(u, flag);
		}
	}
	if (flag & FTMALLOC_SHOW_DATA)
		show_data(dat, flag);
	mem_unlock(dat);
}
