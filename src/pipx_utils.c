/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:46:02 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/05 15:19:43 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	ft_print_err(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		write(1, &str[x], 1);
		x++;
	}
	write(1, "\n", 1);
	exit(-1);
}

int	ft_strlen(char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

int	ft_strncmp(char *str1, char *str2, int len)
{
	int x;

	x = 0;
	while (str1[x] && str2[x] && x < len)
	{
		if (str1[x] != str2[x])
			return (str1[x] - str2[x]);
		x++;
	}
	return (0);
}