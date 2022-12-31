/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:28:28 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/12 20:50:25 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	rtn;
	int	isneg;

	rtn = 0;
	isneg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		isneg -= (*str++ == '-') * 2;
	while (ft_isdigit(*str))
		rtn = *str++ - '0' + rtn * 10;
	return (rtn * isneg);
}
