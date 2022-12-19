/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:54:13 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/12 20:52:20 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*bbzero;

	bbzero = malloc(count * size);
	if (bbzero == 0)
		return (0);
	ft_bzero(bbzero, count * size);
	return (bbzero);
}
