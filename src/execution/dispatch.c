/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:41:06 by averin            #+#    #+#             */
/*   Updated: 2024/02/05 10:30:38 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/**
 * @brief Call redirections function and manage errors
 * 
 * @param cmd command to execute
 * @param exec current execution
 * @return int `C_SUCCESS` or an exit code
 */
static int	manage_redirection(t_cmd *cmd, t_exec *exec, char **path)
{
	t_code	err;

	if (init_pipe(cmd, exec) == C_GEN)
		return (124);
	if (fill_exec(exec, *cmd, path) == C_GEN)
	{
		if (errno == C_NOEXEC)
			return (printf("%s: No permission\n", cmd->args[0]), 127);
		else if (errno == C_NOFILE)
			return (printf("%s: Not found\n", cmd->args[0]), 126);
	}
	err = init_infile(*cmd, exec);
	if (err == C_BAD_USE)
		return (130);
	else if (err == C_GEN || init_outfile(*cmd, exec) == C_GEN)
		return (125);
	return (C_SUCCESS);
}

/**
 * Execute a command
 * @param cmd command to execute
 * @param path environment's path
 * @param envp current environment
 * @return exit code
*/
int	dispatch_cmd(t_cmd *cmd, char **path, char **envp)
{
	t_exec	exec;
	int		pid;
	int		err;

	init_exec(&exec);
	while (cmd)
	{
		err = manage_redirection(cmd, &exec, path);
		if (err != C_SUCCESS)
			return (free(exec.pathname), err);
		pid = do_exec(&exec, envp);
		cmd = find_element(*cmd, T_PIPE);
		if (cmd)
			exec.infile = exec.pipes[0];
	}
	free(exec.pathname);
	return (wait_children(pid));
}
