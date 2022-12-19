/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:18:18 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/12 21:25:25 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getintlen(int n)
{
	int	llen;

	if (n == 0)
		return (1);
	llen = 0;
	if (n < 0)
		llen++;
	while (n)
	{
		llen++;
		n = n / 10;
	}
	return (llen);
}

static int	ft_power(int x)
{
	int	vl;
	int	i;

	vl = 1;
	i = 0;
	if (x <= 0)
		return (1);
	while (i < x)
	{
		vl = vl * 10;
		i++;
	}
	return (vl);
}

static char	*ft_rtnitoa(char *str, int n, int llen)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		llen--;
		str[llen--] = -(n % 10) + '0';
		i = 1;
		n = -(n / 10);
	}
	while (llen > 0)
	{
		str[i] = (n / ft_power(llen - 1)) + '0';
		n = n % ft_power(--llen);
		i++;
	}
	str[i + (*str == '-')] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		llen;
	char	*str;

	llen = ft_getintlen(n);
	if (llen < 1)
		return (0);
	str = malloc(sizeof(char) * (llen + 1));
	if (!str)
		return (NULL);
	return (ft_rtnitoa(str, n, llen));
}
