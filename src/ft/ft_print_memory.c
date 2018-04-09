/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:11:04 by fjacquem          #+#    #+#             */
/*   Updated: 2018/04/09 15:48:22 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void	myputstr(char *s, int n)
{
	int	l;

	l = 0;
	while (l < 16 && l < n)
	{
		if (*s < 127 && *s >= 32)
			write(1, s, 1);
		else
			write(1, ".", 1);
		s++;
		l++;
	}
}

static void	write_content(void *addr, int size, int len)
{
	int	i;

	i = 0;
	while (i < 16 && len + i < size)
	{
		if (*(unsigned char*)(addr + len + i) == 0)
			write(1, "00", 2);
		else
			putline(*(unsigned char*)(addr + len + i), 1);
		if (i % 2)
			write(1, " ", 1);
		i++;
	}
	while (i < 16)
	{
		write(1, "  ", 2);
		if (i % 2)
			write(1, " ", 1);
		i++;
	}
}

void		*ft_print_memory(const void *addr, size_t size)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (len < size)
	{
		ft_printaddr((intptr_t)addr + len);
		write(1, ": ", 2);
		write_content((void*)addr, size, len);
		myputstr((void*)addr + len, size - len);
		write(1, "\n", 1);
		len += 16;
	}
	return ((void*)addr);
}
