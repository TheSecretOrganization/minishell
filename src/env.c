/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:22:06 by averin            #+#    #+#             */
/*   Updated: 2024/02/02 14:04:41 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief get the env value corresping to `item`
 *
 * @param data shell's data
 * @param item item to search
 * @return char* item's value or NULL, need to be freed
 */
char	*ft_getenv(t_data data, char *item)
{
	size_t	i;

	i = -1;
	item = ft_strjoin(item, "=");
	if (!item)
		return (NULL);
	while (data.envp[++i])
	{
		if (ft_strncmp(data.envp[i], item, ft_strlen(item)) == 0)
			return (free(item), ft_substr(data.envp[i],
					ft_strchr(data.envp[i], '=') - data.envp[i] + 1,
					ft_strlen(data.envp[i])));
	}
	return (free(item), NULL);
}
