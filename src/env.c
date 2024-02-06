/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:22:06 by averin            #+#    #+#             */
/*   Updated: 2024/02/06 15:26:07 by abasdere         ###   ########.fr       */
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
	size_t	len;

	i = -1;
	len = ft_strlen(item);
	while (data.envp[++i])
	{
		if ((data.envp[i][len] == '=' || data.envp[i][len] == '\0')
			&& ft_strncmp(data.envp[i], item, len) == 0)
			return (ft_substr(data.envp[i],
					ft_strchr(data.envp[i], '=') - data.envp[i] + 1,
					ft_strlen(data.envp[i])));
	}
	return (NULL);
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

	content = ft_substr(item, 0, ft_strlen(item));
	if (value)
	{
		content = ft_fstrjoin(content, "=", 1);
		if (!content)
			return (C_MEM);
		content = ft_fstrjoin(content, value, 1);
	}
	if (!content)
		return (C_MEM);
	i = -1;
	while (data->envp[++i])
		;
	nenv = ft_calloc(i + 2, sizeof(char *));
	if (!nenv)
		return (free(content), C_MEM);
	i = -1;
	while (data->envp[++i])
		nenv[i] = data->envp[i];
	nenv[i] = content;
	return (free(data->envp), data->envp = nenv, C_SUCCESS);
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
	size_t	len_item;
	char	*content;

	i = -1;
	len_item = ft_strlen(item);
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], item, len_item))
			continue ;
		item = ft_strjoin(item, "=");
		if (!item)
			return (C_MEM);
		if (value)
			content = ft_strjoin(item, value);
		else
			content = ft_substr(item, 0, ft_strlen(item) - 1);
		if (!content)
			return (free(item), C_MEM);
		(free(data->envp[i]), data->envp[i] = content);
		return (free(item), C_SUCCESS);
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
	size_t	len_item;
	size_t	len;
	size_t	i;

	len_item = ft_strlen(item);
	len = -1;
	i = -1;
	while (data->envp[++len])
		;
	nenv = ft_calloc(len, sizeof(char *));
	if (!nenv)
		return (C_MEM);
	while (data->envp[++i])
	{
		if ((data->envp[i][len_item] == '=' || data->envp[i][len_item] == '\0')
			&& ft_strncmp(data->envp[i], item, len_item) == 0)
			free(data->envp[i]);
		else
			nenv[i] = data->envp[i];
	}
	return (free(data->envp), data->envp = nenv, C_SUCCESS);
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

	if (envp == NULL)
		return (C_SUCCESS);
	len = -1;
	while (envp[++len])
		;
	data->envp = ft_calloc(len + 1, sizeof(char *));
	if (!data->envp)
		return (C_MEM);
	i = -1;
	while (envp[++i])
	{
		len = ft_strlen(envp[i]);
		data->envp[i] = ft_calloc(len + 1, sizeof(char));
		if (!data->envp[i])
			return (ft_fsplit(data->envp), C_MEM);
		ft_memcpy(data->envp[i], envp[i], len);
	}
	data->envp[i] = NULL;
	return (C_SUCCESS);
}
