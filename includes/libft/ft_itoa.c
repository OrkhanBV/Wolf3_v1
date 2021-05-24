/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jremarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 05:14:54 by jremarqu          #+#    #+#             */
/*   Updated: 2019/04/28 01:32:15 by jremarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int n)
{
	if (n == INTMIN)
		return (-1);
	else
	{
		if (n < 0)
		{
			return (-n);
		}
		else
		{
			return (n);
		}
	}
}

static char	*ft_itoa_numb(int n, int len, int sign, unsigned long int ten)
{
	char	*numb;
	int		i;

	numb = (char *)malloc(sizeof(char) * (len + sign + 1));
	if (!numb)
		return (NULL);
	i = 0;
	if (sign)
		numb[i++] = '-';
	while (i < (len + sign))
	{
		numb[i] = '0' + (n / ten);
		n %= ten;
		ten /= 10;
		i++;
	}
	numb[i] = '\0';
	return (numb);
}

char	*ft_itoa(int n)
{
	int					len;
	int					sign;
	unsigned long int	ten;

	if (n == INTMIN)
		return (ft_strcpy(ft_strnew(11), "INTMIN"));
	ten = 10;
	len = 1;
	if (n < 0)
	{
		sign = 1;
	}
	else
	{
		sign = 0;
	}
	n = ft_abs(n);
	while (n % (int)ten != n)
	{
		len++;
		ten *= 10;
	}
	ten /= 10;
	return (ft_itoa_numb(n, len, sign, ten));
}
