/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:17:27 by averin            #+#    #+#             */
/*   Updated: 2024/02/14 13:16:20 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Find an executable with a relative path, errno is set in case of error
 * @param cmd relative path
 * @return freeable path or NULL
*/
static char	*find_relative_exec(char *cmd)
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
static char	*find_path_exec(char *cmd, char **path)
{
	char	*exec;
	size_t	i;
	DIR		*dir;

	i = -1;
	while (path[++i])
	{
		exec = ft_strjoin(path[i], cmd);
		if (!exec)
			return (errno = C_MEM, NULL);
		dir = opendir(exec);
		if (dir || errno == ENOENT)
		{
			if (dir)
				closedir(dir);
			free(exec);
			continue ;
		}
		if (access(exec, F_OK | X_OK) == -1)
			return (free(exec), errno = C_NOEXEC, NULL);
		return (exec);
	}
	return (errno = C_NOFILE, NULL);
}

/**
 * @brief Find executable pathname
 *
 * @param exec current execution
 * @param path env's path
 * @return char* the pathname or NULL, errno is set
 */
char	*find_pathname(t_exec *exec, char **path)
{
	if (path == NULL || ft_strchr(exec->args[0], '/'))
		exec->pathname = find_relative_exec(exec->args[0]);
	else
		exec->pathname = find_path_exec(exec->args[0], path);
	return (exec->pathname);
}
