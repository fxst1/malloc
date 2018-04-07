/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:05:02 by fjacquem          #+#    #+#             */
/*   Updated: 2018/03/04 16:35:51 by fxst1            ###   ########.fr       */
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
		v += '0';
		write(STDOUT_FILENO, &v, 1);
	}
}
