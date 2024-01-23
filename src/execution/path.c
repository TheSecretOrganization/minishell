/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:42:17 by averin            #+#    #+#             */
/*   Updated: 2024/01/23 11:44:48 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**get_path(void)
{
	size_t	i;
	char	*path;
	char	*temp;
	char	**result;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	result = ft_split(path, ':');
	if (!result)
		return (NULL);
	i = -1;
	while (result[++i])
	{
		if (result[i][ft_strlen(result[i]) - 1] != '/')
		{
			temp = ft_strjoin(result[i], "/");
			if (!temp)
				return (ft_fsplit(result), NULL);
			(free(result[i]), result[i] = temp);
		}
	}
	return (result);
}
