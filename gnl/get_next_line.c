/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabakar- <sabakar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:15:06 by sabakar-          #+#    #+#             */
/*   Updated: 2024/04/22 16:09:19 by sabakar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*helper_ft(int fd, char *updated)
{
	int		char_num;
	char	*previous;

	char_num = 1;
	previous = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!previous)
		return (NULL);
	while (!has_end(updated) && char_num != 0)
	{
		char_num = read(fd, previous, BUFFER_SIZE);
		if (char_num == -1)
		{
			free(previous);
			return (NULL);
		}
		previous[char_num] = 0;
		updated = ft_strjoin_gnl(updated, previous);
	}
	free(previous);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*updated;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	updated = helper_ft(fd, updated);
	if (!updated || updated[0] == 0)
	{
		free(updated);
		updated = NULL;
		return (NULL);
	}
	line = line_dealer(updated);
	if (updated)
	{
		if (updated[0] == 0)
		{
			free(updated);
			updated = NULL;
		}
	}
	return (line);
}

// int	main(void)
// {
//   int f1;
//   char *s1;

//   f1 = open("./get_next_line.h", O_RDONLY);
//   while (1)
//   {
// 	s1 = get_next_line(f1);
// 	if (!s1)
// 		break ;
// 	printf("%s", s1);
//   }
//   free(s1);
//   close(f1);
//   return (0);
// }
