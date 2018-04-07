/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:44:18 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/03 18:28:07 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		ft_bzero(const void *ptr, size_t size)
{
	unsigned char	*buf;
	size_t			i;

	i = 0;
	buf = (unsigned char*)ptr;
	while (i < size)
	{
		buf[i] = 0;
		i++;
	}
}
