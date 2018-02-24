/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printmem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:21:38 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 18:24:29 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void	putline(intptr_t value, int offset)
{
	if (value >= 16)
	{
		putline(value / 16, offset - 1);
		putline(value % 16, offset - 1);
	}
	else
	{
		if (value && offset > 0)
			write(STDOUT_FILENO, "0", 1);
		if (value > 9)
			value = value - 10 + 'a';
		else
			value += '0';
		write(STDOUT_FILENO, &value, 1);
	}
}

static void	myputstr(char *s, int n)
{
	int	l;

	l = 0;
	while (l < 16 && l < n)
	{
		if (*s < 127 && *s >= 32)
			write(STDOUT_FILENO, s, 1);
		else
			write(STDOUT_FILENO, ".", 1);
		s++;
		l++;
	}
}

static int	sizeline(intptr_t v)
{
	intptr_t l;

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
			write(STDOUT_FILENO, "00", 2);
		else
			putline(*(unsigned char*)(addr + len + i), 1);
		if (i % 2)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	while (i < 16)
	{
		write(STDOUT_FILENO, "  ", 2);
		if (i % 2)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}

void		*ft_print_memory(const void *addr, size_t size)
{
	size_t		len;
	int			i;
	intptr_t	tmp;

	len = 0;
	i = 0;
	while (len < size)
	{
		tmp = (intptr_t)addr + len;
		i = 8 - sizeline(tmp);
		while (i >= 0)
		{
			write(STDOUT_FILENO, "0", 1);
			i--;
		}
		putline(tmp, 0);
		write(STDOUT_FILENO, ": ", 2);
		write_content((void*)addr, size, len);
		myputstr((void*)addr + len, size - len);
		write(STDOUT_FILENO, "\n", 1);
		len += 16;
	}
	return ((void*)addr);
}
