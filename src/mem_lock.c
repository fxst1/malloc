/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_lock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 11:18:28 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/04 11:24:01 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

#ifndef NO_MT_SAFE

void 		mem_lock(t_mcfg *dat)
{
	pthread_mutex_lock(&dat->lock);
}

#else

void 		mem_lock(t_mcfg *dat)
{
	(void)dat;
}

#endif
