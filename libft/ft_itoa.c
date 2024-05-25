/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:20:30 by zelbassa          #+#    #+#             */
/*   Updated: 2023/11/15 19:57:43 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nbr(int n)
{
	int		len;

	len = 0;
	if (n <= 0)
		len ++;
	while (n != 0)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		neg;
	char	*ptr;
	long	nb;

	len = len_nbr(n);
	neg = 0;
	nb = (long)n;
	if (n < 0)
	{
		neg = 1;
		nb = -nb;
	}
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	while (len--)
	{
		ptr[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (neg)
		ptr[0] = '-';
	return (ptr);
}
