/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:58:12 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 17:53:04 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

#ifndef NO_MT_SAFE

void		mem_lock(t_mcfg *dat)
{
	(void)dat;
}

void		mem_unlock(t_mcfg *dat)
{
	(void)dat;
}

#else

void		mem_lock(t_mcfg *dat)
{
	pthread_mutex_lock(&dat->lock);
}

void		mem_unlock(t_mcfg *dat)
{
	pthread_mutex_unlock(&dat->lock);
}

#endif
