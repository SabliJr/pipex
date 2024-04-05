/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:43:08 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/05 16:46:00 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"
#include <stdio.h>

int	ft_count_words(char *str, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (str[x] == ' ' || str[x] == '\t')
		x++;
	while (str[x])
	{
		while (str[x] == 32 || str[x] == '\t')
			x++;
		while ((str[x] != 32 || str[x] != '\t') && str[x])
			x++;
		if (str[x])
			count++;
		// x++;
	}
	return (count);
}

char	**ft_split(char *str, char sp)
{
	int x;
	int y;
	int len;
	char **res;

	x = 0;
	y = 0;
	res = NULL;
	len = ft_count_words(str, sp);
	res = (char *)malloc(sizeof(char *) * len + 1);
	if (!res)
		return (NULL);
}