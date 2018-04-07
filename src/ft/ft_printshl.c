/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printshl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 10:54:07 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/03 18:03:12 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void		ft_printshl(const char *s, intptr_t hex)
{
	ft_printstr(s);
	ft_printstr("0x");
	ft_printhex(hex);
	write(STDOUT_FILENO, "\n", 1);
}
