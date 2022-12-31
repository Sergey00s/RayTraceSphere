/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:20:38 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/12 21:22:19 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dst == src || !n)
		return (dst);
	if (!dst && !src)
		return (0);
	d = (char *)dst;
	s = (const char *)src;
	while (n--)
		d[n] = s[n];
	return (dst);
}
