/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:17:27 by averin            #+#    #+#             */
/*   Updated: 2024/01/24 14:09:18 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Find an executable with a relative path, errno is set in case of error
 * @param cmd relative path
 * @return freeable path or NULL
*/
char	*find_relative_exec(char *cmd)
{
	if (access(cmd, F_OK) == -1)
		return (errno = C_NOFILE, NULL);
	if (access(cmd, F_OK | X_OK) == -1)
		return (errno = C_NOEXEC, NULL);
	cmd = ft_strdup(cmd);
	if (!cmd)
		return (errno = C_MEM, NULL);
	return (cmd);
}

/**
 * Find an executable in the path
 * @param cmd command name
 * @param path list of path entries
 * @return path or NULL
*/
char	*find_path_exec(char *cmd, char **path)
{
	char	*exec;
	size_t	i;

	i = -1;
	while (path[++i])
	{
		exec = ft_strjoin(path[i], cmd);
		if (!exec)
			return (errno = C_MEM, NULL);
		if (access(exec, F_OK) == -1)
		{
			free(exec);
			continue ;
		}
		if (access(exec, F_OK | X_OK) == -1)
			return (free(exec), errno = C_NOEXEC, NULL);
		return (exec);
	}
	return (errno = C_NOFILE, NULL);
}
