#include <ftmalloc.h>

static void	print_info(t_area *a)
{
	t_blk	*b;

	if (a->blktype == FTMALLOC_TINY)
		write(STDOUT_FILENO, "TINY : ", 7);
	else if (a->blktype == FTMALLOC_SMALL)
		write(STDOUT_FILENO, "SMALL : ", 7);
	else
		write(STDOUT_FILENO, "BIG : ", 7);
	mem_printaddr(a->psize, -1, 1);
	write(STDOUT_FILENO, " (", 2);
	mem_printnum(a->psize);
	write(STDOUT_FILENO, ")", 1);
	write(STDOUT_FILENO, "\n", 1);
	b = a->blocks;
	while (b)
	{
		mem_printaddr((unsigned long)b->addr, FTMALLOC_DBG_MAXDIGIT, 1);
		write(STDOUT_FILENO, " - ", 3);
		mem_printaddr((unsigned long)b->addr + b->allocsize, FTMALLOC_DBG_MAXDIGIT, 1);
		write(STDOUT_FILENO, " : ", 3);
		if (!b->freed)
		{
			mem_printnum(b->allocsize);
			write(STDOUT_FILENO, " bytes\n", 7);
		}
		else
			write(STDOUT_FILENO, "Unused block\n", 13);
		b = b->next;
	}
}

static void	print_info_mem(t_area *a)
{
	t_blk	*b;

	if (a->blktype == FTMALLOC_TINY)
		write(STDOUT_FILENO, "TINY : ", 7);
	else if (a->blktype == FTMALLOC_SMALL)
		write(STDOUT_FILENO, "SMALL : ", 7);
	else
		write(STDOUT_FILENO, "BIG : ", 7);
	mem_printaddr(a->psize, -1, 1);
	write(STDOUT_FILENO, " (", 2);
//	mem_printnum(a->psize);
	mem_printnum(a->nblk);
	write(STDOUT_FILENO, ")", 1);
	write(STDOUT_FILENO, "\n", 1);
	b = a->blocks;
	while (b)
	{
		mem_printaddr((unsigned long)b->addr, FTMALLOC_DBG_MAXDIGIT, 1);
		write(STDOUT_FILENO, " - ", 3);
		mem_printaddr((unsigned long)b->addr + b->allocsize, FTMALLOC_DBG_MAXDIGIT, 1);
		write(STDOUT_FILENO, " : ", 3);
		if (!b->freed)
		{
			mem_printnum(b->allocsize);
			write(STDOUT_FILENO, " bytes\n", 7);
			ft_print_memory(b->addr, b->allocsize);
		}
		else
			write(STDOUT_FILENO, "Unused block\n", 13);
		b = b->next;
	}
}

void		show_alloc_ex(void)
{
	t_mcfg	*dat;
	t_area	*a;

	dat = mem_get_data();
	a = dat->areas;
	while (a)
	{
		print_info(a);
		a = a->next;
	}
}

void		show_alloc_mem_ex(void)
{
	t_mcfg	*dat;
	t_area	*a;

	dat = mem_get_data();
	a = dat->areas;
	while (a)
	{
		print_info_mem(a);
		a = a->next;
	}	
}