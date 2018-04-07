/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:22:40 by fjacquem          #+#    #+#             */
/*   Updated: 2018/04/03 18:03:51 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*ft_strcat(char *dst, const char *src)
{
	char	*tmp;

	tmp = dst;
	while (*dst)
		dst++;
	while (*src)
	{
		*dst = *src;
		src++;
		dst++;
	}
	*dst = 0;
	return (tmp);
}
