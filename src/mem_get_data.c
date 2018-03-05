/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 18:45:34 by fxst1             #+#    #+#             */
/*   Updated: 2018/03/04 21:50:40 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>

static t_mcfg	*get_data(void)
{
	static t_mcfg	cfg;

	return (&cfg);
}

t_mcfg 			*mem_get_data(void)
{
	static int		is_init = 0;
	t_mcfg			*data;

	data = get_data();
	if (!is_init)
	{
		data->expected = 0x0;
		data->opts.prot = PROT_READ | PROT_WRITE;
		data->opts.flags = MAP_ANONYMOUS | MAP_PRIVATE;
		data->opts.fd = -1;
		data->opts.offset = 0;
		data->areas = NULL;
		pthread_mutex_init(&data->lock, NULL);
		is_init = 1;
	}
	data->psize = getpagesize();
	return (data);
}
