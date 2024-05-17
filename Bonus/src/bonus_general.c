/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:19:08 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/17 18:29:37 by sabakar-         ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_print_err(char *str)
{
	int x;
	int len;
	char *new_str;

	len = ft_strlen(str);
	x = 0;
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return ;
	while (str[x])
	{
		new_str[x] = str[x];
		x++;
	}
	new_str[x] = '\n';
	write(2, new_str, len + 1);
	free(new_str);
}