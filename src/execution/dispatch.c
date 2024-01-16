/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:41:06 by averin            #+#    #+#             */
/*   Updated: 2024/01/16 16:27:52 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/**
 * Free execution
 * @param exec struct to free
*/
void	free_exec(t_exec exec)
{
	free(exec.pathname);
	ft_fsplit(exec.args);
}

/**
 * Init the exec structure
 * @param exec structure to init
 * @param cmd cmd to init from
 * @param path the path
 * @return SUCCESS 
*/
static int	init_exec(t_exec *exec, t_cmd cmd, char **path)
{
	exec->args = cmd.args;
	if (ft_strchr(exec->args[0], '/'))
		exec->pathname = find_relative_exec(exec->args[0]);
	else
		exec->pathname = find_path_exec(exec->args[0], path);
	if (!exec->pathname)
		return (C_GEN);
	exec->infile = -1;
	exec->outfile = -1;
	exec->pipes[0] = -1;
	exec->pipes[1] = -1;
	return (C_SUCCESS);
}

/**
 * Execute a command
 * @param cmd command to execute
 * @param path environment's path
 * @return exit code
*/
int	dispatch_cmd(t_cmd *cmd, char **path)
{
	t_exec	exec;
	int		pid;

	if (init_exec(&exec, *cmd, path) == C_GEN)
	{
		if (errno == C_NOEXEC)
			return (printf("No permission\n"), 127);
		else if (errno == C_NOFILE)
			return (printf("Not found\n"), 126);
	}
	pid = do_exec(&exec, NULL);
	waitpid(pid, NULL, 0);
	free(exec.pathname);
	return (0);
}
