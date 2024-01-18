/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freejoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:15:01 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/18 16:15:07 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_alloc(char *s1, char *s2, int nb_alloc)
{
	if (nb_alloc == 2)
	{
		free(s1);
		free(s2);
	}
	else if (nb_alloc == -1)
		free(s1);
	else if (nb_alloc == 1)
		free(s2);
}

char	*ft_freejoin(char *s1, char *s2, int nb_alloc)
{
	size_t	i;
	size_t	len_s1;
	char	*join;

	if (!s1 || !s2)
		return (free_alloc(s1, s2, nb_alloc), NULL);
	len_s1 = ft_strlen(s1);
	join = ft_calloc(len_s1 + ft_strlen(s2) + 1, sizeof(char));
	if (!join)
		return (free_alloc(s1, s2, nb_alloc), NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	i = -1;
	while (s2[++i])
		join[i + len_s1] = s2[i];
	return (free_alloc(s1, s2, nb_alloc), join);
}
