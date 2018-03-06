/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:42:30 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/06 16:06:13 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void 	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i = 0;

	s = (unsigned char*)src;
	d = (unsigned char*)dst;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
