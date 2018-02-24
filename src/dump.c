/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:54:04 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 16:24:16 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void			alloc_dump_process(const int fd, const void *addr,
						size_t allocsize)
{
	write(fd, "FT", 2);
	write(fd, &allocsize, sizeof(allocsize));
	write(fd, addr, allocsize);
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
				alloc_dump_process(fd, addr, b->allocsize);
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
