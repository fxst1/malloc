/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_get_total.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 21:27:52 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/04 21:35:01 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

size_t			mem_get_total(size_t value, size_t add)
{
	static size_t	total = 0;

	if (!add)
		total -= value;
	else
		total += value;
	return (total);
}
