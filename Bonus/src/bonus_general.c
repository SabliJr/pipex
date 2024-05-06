/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:19:08 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/06 07:17:31 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	ft_free(char **arr)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		free(arr[x]);
		arr[x] = NULL;
		x++;
	}
	free(arr);
	arr = NULL;
}

int	ft_strncmp_b(char *s1, char *s2, int len)
{
	int	x;

	x = 0;
	while (x < len)
	{
		if (s1[x] != s2[x])
			return (s1[x] - s2[x]);
		x++;
	}
	return (0);
}

int	ft_strlen(char *sr)
{
	int	x;

	x = 0;
	while (sr[x])
		x++;
	return (x);
}

void	ft_putstr(char *sr)
{
	int x;

	x = 0;
	while (sr[x])
	{
		write(2, &sr[x], 1);
		x++;
	}
	write(2, "\n", 1);
}
