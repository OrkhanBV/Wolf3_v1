/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 21:39:42 by jremarqu          #+#    #+#             */
/*   Updated: 2020/04/25 00:37:40 by jremarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned char	*ptr_dst;
	size_t			i;

	ptr_dst = (unsigned char *)dst;
	i = 0;
	while (src[i] != '\0')
	{
		ptr_dst[i] = src[i];
		i++;
	}
	ptr_dst[i] = '\0';
	return ((char *)ptr_dst);
}
