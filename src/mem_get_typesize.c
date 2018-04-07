/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_get_typesize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 11:26:45 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/04 11:28:30 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

size_t					mem_get_typesize(size_t allocsize)
{
	if (allocsize <= FTMALLOC_TINY)
		return (FTMALLOC_TINY);
	else if (allocsize <= FTMALLOC_SMALL)
		return (FTMALLOC_SMALL);
	return (allocsize);
}
