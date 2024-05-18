/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:43:22 by sabakar-          #+#    #+#             */
/*   Updated: 2024/05/18 15:57:00 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > INT_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	ft_bzero(void *a, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)a)[i] = 0;
		i++;
	}
}

int	ft_init_data(t_pipex_bonus *data, int ac, char *av[], char *envp[])
{
	if (ac < 5)
		ft_err_handler(data, 3, NULL);
	if (ft_strncmp_b(av[1], "here_doc", 8) == 0)
		data->here_doc = TRUE;
	else
		data->here_doc = FALSE;
	if (data->here_doc && ac < 6)
		ft_err_handler(data, 3, NULL);

	if (data->here_doc)
		data->pids = malloc(sizeof(pid_t) * ac - 4);
	else
		data->pids = malloc(sizeof(pid_t) * ac - 3);
	data->paths = ft_get_paths(envp);
	if (data->here_doc)
		return (3);
	return (2);
}

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*new_str;
	size_t	x;

	if (!s)
		return (NULL);
	x = 0;
	len = ft_strlen(s) + 1;
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (!new_str)
		return (NULL);
	while (x < len)
	{
		new_str[x] = s[x];
		x++;
	}
	return (new_str);
}
