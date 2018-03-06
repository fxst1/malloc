/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 08:54:04 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/06 11:23:15 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

void 		*calloc(size_t nmemb, size_t size)
{
	ft_printstr("Calloc\n");
	void 	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr)
		ft_bzero(ptr, nmemb * size);
	ft_printstr("End Calloc\n");
	return (ptr);
}
