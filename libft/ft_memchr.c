/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:17:38 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/12 21:23:47 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int c, size_t n)
{
	unsigned char	*pptr;
	size_t			i;

	pptr = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		if (pptr[i] == (unsigned char)c)
			return ((void *)&pptr[i]);
		i++;
	}
	return (0);
}
