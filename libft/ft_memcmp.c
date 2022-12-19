/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:57:54 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/12 21:04:22 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	unsigned char	*pp1;
	unsigned char	*pp2;
	size_t			i;

	i = 0;
	pp1 = (unsigned char *)ptr1;
	pp2 = (unsigned char *)ptr2;
	while (i < n)
	{
		if (pp1[i] != pp2[i])
			return (pp1[i] - pp2[i]);
		i++;
	}
	return (0);
}
