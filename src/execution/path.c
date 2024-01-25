/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:42:17 by averin            #+#    #+#             */
/*   Updated: 2024/01/24 10:14:36 by abasdere         ###   ########.fr       */
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
				(ft_fsplit(result), exit(C_MEM));
			(free(result[i]), result[i] = temp);
		}
	}
	return (result);
}
