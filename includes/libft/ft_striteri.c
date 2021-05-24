/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:35:53 by jremarqu          #+#    #+#             */
/*   Updated: 2019/04/29 03:15:13 by jremarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (s == 0 || f == 0)
		return ;
	i = 0;
	while (i < ft_strlen(s))
	{
		f(i, &s[i]);
		i++;
	}
}
