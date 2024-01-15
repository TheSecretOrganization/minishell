/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:41:06 by averin            #+#    #+#             */
/*   Updated: 2024/01/15 12:46:36 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/**
 * Find an executable with a relative path
 * @param cmd relative path
 * @return path or NULL
*/
static char	*find_relative_exec(char *cmd)
{
	if (access(cmd, F_OK) == -1)
		return (errno = E_NOFILE, NULL);
	if (access(cmd, F_OK | X_OK) == -1)
		return (errno = E_NOEXEC, NULL);
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

	i = -1;
	while (path[++i])
	{
		exec = ft_strjoin(cmd, path[i]);
		if (!exec)
			return (errno = E_MEM, NULL);
		if (access(exec, F_OK) == -1)
		{
			free(exec);
			continue ;
		}
		if (access(exec, F_OK | X_OK) == -1)
			return (free(exec), errno = E_NOEXEC, NULL);
		return (exec);
	}
	return (free(exec), errno = E_NOFILE, NULL);
}

/**
 * Execute a command
 * @param cmd command to execute
 * @param path environment's path
 * @return exit code
*/
int	exec_cmd(t_cmd *cmd, char **path)
{

	pid = do_exec(exec, cmd->args, NULL, (int []){0, 1});
	waitpid(pid, NULL, 0);
	return (0);
}
