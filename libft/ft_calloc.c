/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsauvag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:05:53 by chsauvag          #+#    #+#             */
/*   Updated: 2024/10/23 13:42:28 by chsauvag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			total_s;

	i = 0;
	total_s = nmemb * size;
	if (nmemb != 0 && size != 0 && total_s / nmemb != size)
	{
		return (NULL);
	}
	ptr = malloc(total_s);
	if (!(ptr))
	{
		return (NULL);
	}
	while (i < total_s)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

/*int	main()
{
	int *array = (int *)ft_calloc(5, sizeof(int));
	int i = 0;
	if (array == NULL)
	{
		printf("Allocation failed!\n");
		return 1;
	}
	while(i < 5)
	{
		printf("%d ", array[i]);
		i++;
	}
	printf("\n");
	free(array);
	return 0;
}*/
