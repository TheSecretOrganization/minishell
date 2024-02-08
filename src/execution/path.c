/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:42:17 by averin            #+#    #+#             */
/*   Updated: 2024/02/07 14:41:41 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * @brief Get the path object
 *
 * @param data data of the program
 * @return int C_SUCCESS or C_MEM
 */
int	get_path(t_data *data)
{
	size_t	i;
	char	*temp;
	char	**result;

	temp = ft_getenv(*data, "PATH");
	if (!temp)
		return (ft_fsplit(data->path), data->path = NULL, C_SUCCESS);
	result = ft_split(temp, ':');
	(free(temp), i = -1);
	if (!result)
		return (C_MEM);
	while (result[++i])
	{
		if (result[i][ft_strlen(result[i]) - 1] != '/')
		{
			temp = ft_strjoin(result[i], "/");
			if (!temp)
				return (ft_fsplit(result), C_MEM);
			(free(result[i]), result[i] = temp);
		}
	}
	return (ft_fsplit(data->path), data->path = result, C_SUCCESS);
}
