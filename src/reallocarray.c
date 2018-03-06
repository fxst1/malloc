/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocarray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 10:38:59 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/06 13:21:42 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void 			*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	//ft_printstr("ReallocArray\n");
	return (realloc(ptr, nmemb * size));
}
