/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:56:27 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/09 15:08:59 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	cchar;
	int				i;

	cchar = (unsigned char)c;
	i = ft_strlen(s) + 1;
	while (i >= 0)
	{
		i--;
		if (s[i] == cchar)
			return ((char *)&s[i]);
	}
	return (NULL);
}
