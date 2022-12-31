/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:09:20 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/12 21:09:30 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;

	j = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = dstlen;
	if (dstsize == 0)
		return (srclen);
	if (dstsize < dstlen)
		return (srclen + dstsize);
	while (src[j] && (dstlen + j) < dstsize)
		dst[i++] = src[j++];
	if ((dstlen + j) == dstsize && dstlen < dstsize)
		dst[--i] = '\0';
	else
		dst[i] = '\0';
	return (srclen + dstlen);
}
