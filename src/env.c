/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:22:06 by averin            #+#    #+#             */
/*   Updated: 2024/02/02 16:01:24 by averin           ###   ########.fr       */
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

t_code	ft_unenv(t_data *data, char *item)
{
	char	**nenv;
	size_t	len;
	size_t	i;

	item = ft_strjoin(item, "=");
	if (!item)
		return (C_MEM);
	len = -1;
	i = -1;
	while (data->envp[++len])
		;
	nenv = ft_calloc(len, sizeof(char *));
	if (!nenv)
		return (free(item), C_MEM);
	while (data->envp[++i] && ft_strncmp(data->envp[i], item, ft_strlen(item)))
		nenv[i] = data->envp[i];
	free(data->envp[i]);
	while (data->envp[++i])
		nenv[i - 1] = data->envp[i];
	nenv[i - 1] = NULL;
	return (free(item), free(data->envp), data->envp = nenv, C_SUCCESS);
}
