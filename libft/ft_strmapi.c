/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:21:12 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/12 21:10:52 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	llen;
	char	*ml;

	if (!s)
		return (NULL);
	llen = ft_strlen(s);
	ml = malloc((llen + 1) * sizeof(char));
	if (!ml)
		return (NULL);
	i = 0;
	while (i < llen)
	{
		ml[i] = f(i, s[i]);
		i++;
	}
	ml[i] = '\0';
	return (ml);
}
