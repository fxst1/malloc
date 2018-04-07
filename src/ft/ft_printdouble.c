/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdouble.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:05:13 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 18:07:14 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void		ft_printdouble(double d, unsigned int precision)
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
	ft_printnum(dec);
	write(STDOUT_FILENO, ",", 1);
	ft_printnum(fl);
}
