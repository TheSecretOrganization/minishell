/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:17:27 by averin            #+#    #+#             */
/*   Updated: 2024/01/29 09:26:32 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin.h"

static	cmp_cmd(char *name, char *cmd)
{
	return (ft_strncmp(name, cmd, ft_strlen(name) + 1));
}

static	set_cmd(t_exec *exec, int (*f)(t_exec *))
{
	exec->is_builtin = 1;
	exec->builtin = f;
}

int	is_builtin(t_cmd cmd, t_exec *exec)
{
	char	*name;

	name = cmd.args[0];
	if (cmp_cmd(name, "echo"))
		set_cmd(exec, cmd_echo);
	if (cmp_cmd(name, "cd"))
		set_cmd(exec, cmd_cd);
	if (cmp_cmd(name, "pwd"))
		set_cmd(exec, cmd_pwd);
	if (cmp_cmd(name, "export"))
		set_cmd(exec, cmd_export);
	if (cmp_cmd(name, "unset"))
		set_cmd(exec, cmd_unset);
	if (cmp_cmd(name, "env"))
		set_cmd(exec, cmd_env);
	if (cmp_cmd(name, "exit"))
		set_cmd(exec, cmd_exit);
	return (exec->is_builtin);
}

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
