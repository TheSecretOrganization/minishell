/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:07:52 by averin            #+#    #+#             */
/*   Updated: 2023/08/11 14:11:38 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*r;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	r = (char *) ft_calloc(size, sizeof(char));
	if (!r)
		return (NULL);
	ft_strlcat(r, s1, size);
	ft_strlcat(r, s2, size);
	return (r);
}
