/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:32:16 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/09 18:41:44 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	llen;

	if (!s)
		return ;
	llen = ft_strlen(s);
	i = 0;
	while (i < llen)
	{
		f(i, &s[i]);
		i++;
	}
}
