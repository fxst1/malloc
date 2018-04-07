/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:03:06 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/03 18:03:22 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

void			ft_printstr(const char *s)
{
	write(1, s, ft_strlen(s));
}
