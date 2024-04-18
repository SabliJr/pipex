#include "./pipex.h"

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

void ft_free (char **arr)
{
	int x;

	x = 0;
	if (!arr)
		return ;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}