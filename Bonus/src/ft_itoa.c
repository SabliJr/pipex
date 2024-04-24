/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:33:59 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/23 11:06:51 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static int	nbr_leng(int nb)
{
	int	count;

	count = 0;
	if (nb <= 0)
	{
		count++;
		nb *= -1;
	}
	while (nb)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

char	*ft_itoa(int nbr)
{
	int x;
	char *res;
	int len;

	len = nbr_leng(nbr);
	x = 0;
	if (nbr == -2147483648)
		return ("-2147483648");
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	if (nbr == 0)
		res[0] = '0';
	if (nbr < 0)
	{
		res[0] = '-';
		nbr = -nbr;
	}
	res[len--] = '\0';
	while (nbr)
	{
		res[len] = nbr % 10 + '0';
		len--;
		nbr = nbr / 10;
	}
	return (res);
}