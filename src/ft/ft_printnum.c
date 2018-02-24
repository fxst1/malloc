/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:05:02 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 18:07:09 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void		ft_printnum(intptr_t v)
{
	if (v >= 10)
	{
		ft_printnum(v / 10);
		ft_printnum(v % 10);
	}
	else
	{
		v = (v <= 9 ? v + '0' : v - 10 + 'A');
		write(1, &v, 1);
	}
}
