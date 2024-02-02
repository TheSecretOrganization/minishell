/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:22:06 by averin            #+#    #+#             */
/*   Updated: 2024/02/02 16:36:00 by averin           ###   ########.fr       */
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

/**
 * @brief Put a new `item` in env with the `value`
 * 
 * @param data shell's data
 * @param item value's key
 * @param value value to put
 * @return t_code C_SUCCESS or C_MEM
 */
static t_code	ft_putenv(t_data *data, char *item, char *value)
{
	size_t	i;
	char	**nenv;
	char	*content;

	item = ft_strjoin(item, "=");
	if (!item)
		return (C_MEM);
	content = ft_strjoin(item, value);
	if (!value)
		return (free(item), C_MEM);
	i = -1;
	while (data->envp[++i])
		;
	nenv = ft_calloc(i + 1, sizeof(char *));
	if (!nenv)
		return (free(item), free(content), C_MEM);
	i = -1;
	while (data->envp[++i])
		nenv[i] = data->envp[i];
	nenv[i] = content;
	nenv[i + 1] = NULL;
	return (free(item), C_SUCCESS);
}

/**
 * @brief Set or put a `value` to the env at `item` index
 *
 * @param data shell's data
 * @param item value's key
 * @param value value to set
 * @return t_code C_SUCCESS or C_MEM
 */
t_code	ft_setenv(t_data *data, char *item, char *value)
{
	size_t	i;
	char	*content;

	i = -1;
	while (data->envp[++i] && ft_strncmp(data->envp[i], item, ft_strlen(item)))
	{
		item = ft_strjoin(item, "=");
		if (!item)
			return (C_MEM);
		content = ft_strjoin(item, value);
		if (!content)
			return (free(item), C_MEM);
		free(data->envp[i]);
		data->envp[i] = content;
		return (free(content), free(item), C_SUCCESS);
	}
	return (ft_putenv(data, item, value));
}

/**
 * @brief Remove an item from the env
 * 
 * @param data shell's data
 * @param item item to remove
 * @return t_code C_SUCCESS or C_MEM
 */
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

/**
 * @brief Copy the envp toa full malloced array
 * 
 * @param data shell's data
 * @param envp env to copy in `data`
 * @return t_code C_SUCCESS or C_MEM
 */
t_code	cpy_envp(t_data *data, char **envp)
{
	size_t	len;
	size_t	i;

	len = -1;
	while (envp[++len])
		;
	data->envp = ft_calloc(len + 1, sizeof(char *));
	if (!data->envp)
		return (C_MEM);
	i = -1;
	while (envp[++i])
	{
		data->envp[i] = ft_calloc(ft_strlen(envp[i]) + 1, sizeof(char));
		if (!data->envp[i])
			return (ft_fsplit(data->envp), C_MEM);
		ft_memcpy(data->envp[i], envp[i], ft_strlen(envp[i]));
	}
	data->envp[i] = NULL;
	return (C_SUCCESS);
}
