/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_is_overlap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 09:16:13 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/22 09:20:27 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

int 		mem_is_overlap(t_mcfg *cfg)
{
	t_area		*a;

	a = cfg->areas;
	if (!a)
		return (0);
	while (a)
	{
		if (ft_memcmp((char*)a->magic, FTMALLOC_MAGIC, 16))
		{
			write(STDERR_FILENO, "Ftmalloc: overlap\n", 18);
			exit(EXIT_FAILURE);
			return (1);
		}
		a = a->next;
	}
	return (0);
	(void)cfg;
}
