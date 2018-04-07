/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_unlock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 11:18:28 by fxst1             #+#    #+#             */
/*   Updated: 2018/04/03 17:52:59 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

#ifndef NO_MT_SAFE

void		mem_unlock(t_mcfg *dat)
{
	pthread_mutex_unlock(&dat->lock);
}

#else

void		mem_unlock(t_mcfg *dat)
{
	(void)dat;
}

#endif
