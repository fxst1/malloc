/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:11:04 by fjacquem          #+#    #+#             */
/*   Updated: 2018/03/06 13:19:40 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void	putline(int value, int offset)
{
	if (value >= 16)
	{
		putline(value / 16, offset - 1);
		putline(value % 16, offset - 1);
	}
	else
	{
		if (value && offset > 0)
			write(1, "0", 1);
		if (value > 9)
			value += 'a' - 10;
		else
			value += '0';
		write(1, &value, 1);
	}
}

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

static int	sizeline(int v)
{
	int l;

	l = 0;
	if (v >= 16)
	{
		l += sizeline(v / 16);
		l += sizeline(v % 16);
	}
	else
		return (1);
	return (l);
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
		i = 8 - sizeline((size_t)addr + len);
		while (i)
		{
			write(1, "0", 1);
			i--;
		}
		putline((size_t)addr + len, 0);
		write(1, ": ", 2);
		write_content((void*)addr, size, len);
		myputstr((void*)addr + len, size - len);
		write(1, "\n", 1);
		len += 16;
	}
	return ((void*)addr);
}
