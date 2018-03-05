/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:01:04 by fjacquem          #+#    #+#             */
/*   Updated: 2018/03/05 11:05:28 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static void		ft_printhex2(intptr_t v, size_t *n)
{
	if (v >= 16)
	{
		ft_printhex2(v / 16, n);
		ft_printhex2(v % 16, n);
	}
	else
	{
		(*n)++;
		v = (v <= 9 ? v + '0' : v - 10 + 'a');
		write(STDOUT_FILENO, &v, 1);
	}
}

static void		ft_printhex1(intptr_t v, int max, int show_x)
{
	size_t	n;

	n = 0;
	if (!v)
	{
		if (show_x)
			write(STDOUT_FILENO, "0x0", 3);
		else
			write(STDOUT_FILENO, "0", 1);
	}
	else
	{
		if (show_x)
			write(STDOUT_FILENO, "0x", 2);
		ft_printhex2((unsigned long)v, &n);
		if (max > 0)
			while (n < (size_t)max)
			{
				write(STDOUT_FILENO, "0", 1);
				n++;
			}
	}
}


void			ft_printaddr(intptr_t v)
{
	ft_printhex1(v, FTMALLOC_DBG_MAXDIGIT, 1);
}

void			ft_printhex(intptr_t v)
{
	ft_printhex1(v, -1, 0);
}
