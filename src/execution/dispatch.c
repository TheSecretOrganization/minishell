/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:41:06 by averin            #+#    #+#             */
/*   Updated: 2024/02/12 09:47:05 by averin           ###   ########.fr       */
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
static int	prepare_exec(t_cmd *cmd, t_exec *exec, char **path)
{
	int	err;

	if (init_pipe(cmd, exec) == C_GEN)
		return (124);
	reset_exec(exec);
	err = init_redirections(*cmd, exec);
	if (err == C_BAD_USE)
		return (130);
	else if (err == C_GEN)
		return (125);
	err = fill_exec(exec, *cmd, path);
	if (err != C_SUCCESS)
		return (err);
	return (C_SUCCESS);
}

/**
 * Execute a command
 * @param data data of the program
 * @return exit code
*/
int	dispatch_cmd(t_data *data)
{
	t_exec	exec;
	int		pid;
	int		err;

	pid = -1;
	init_exec(&exec, data);
	while (exec.target)
	{
		err = prepare_exec(exec.target, &exec, data->path);
		if (exec.args == NULL || err != C_SUCCESS)
			return (free(exec.pathname), err);
		if (exec.is_builtin)
			pid = exec_builtin(&exec);
		else
			do_exec(&exec, data->envp, &pid);
		exec.target = find_element(*(exec.target), T_PIPE);
		if (exec.target)
			exec.infile = exec.pipes[0];
	}
	free(exec.pathname);
	if (exec.is_builtin)
		return (pid);
	return (wait_children(pid));
}
