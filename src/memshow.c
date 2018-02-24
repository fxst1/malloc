/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memshow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:00:40 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 20:13:42 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void		show_waste(t_mcfg *dat)
{
	size_t		used;
	size_t		unused;

	used = mem_get_page_usage(dat->areas);
	unused = mem_get_unused(dat->areas);
	write(STDOUT_FILENO, "used:\t", 7);
	ft_printnum(used);
	write(STDOUT_FILENO, " bytes\n", 7);
	write(STDOUT_FILENO, "unused:\t", 8);
	ft_printnum(unused);
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
		ft_printnum(u.ru_majflt);
		write(STDOUT_FILENO, "\n", 1);
	}
	if (flag & FTMALLOC_SHOW_RES_SOFTPAGE)
	{
		write(STDOUT_FILENO, "\tsoft page faults: ", 19);
		ft_printnum(u.ru_minflt);
		write(STDOUT_FILENO, "\n", 1);
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
