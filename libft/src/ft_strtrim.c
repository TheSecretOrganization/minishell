/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:17:10 by averin            #+#    #+#             */
/*   Updated: 2023/11/07 11:10:01 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(const char *s, char c)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	len;
	size_t	i;

	start = 0;
	while (is_in(set, s1[start]))
		start++;
	i = -1;
	len = 0;
	while (s1[start + ++i])
	{
		if (!is_in(set, s1[start + i]))
			len = i + 1;
	}
	return (ft_substr(s1, start, len));
}
