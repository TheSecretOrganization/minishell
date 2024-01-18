/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:41:06 by averin            #+#    #+#             */
/*   Updated: 2024/01/18 15:07:09 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/**
 * Read redirections from command and set it to exec
 * @param cmd command from wich read redirections
 * @param exec where to store opened fds
 * @result C_SUCCESS or C_GEN when error
*/
static int	init_redirect(t_cmd *cmd, t_exec *exec)
{
	void	*element;

	element = find_element(*cmd, T_INFILE);
	if (element != NULL)
	{
		if (exec->pipes[0] != -1)
			(close(exec->pipes[0]), exec->pipes[0] = -1);
		exec->infile = open(element, O_RDONLY);
		if (exec->infile == -1)
			return (perror(element), C_GEN);
	}
	element = find_element(*cmd, T_OUTFILE);
	if (element != NULL)
	{
		exec->outfile = open(element, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (exec->outfile == -1)
		{
			if (exec->pipes[1] != -1)
				(close(exec->pipes[1]), exec->pipes[1] = -1);
			perror(element);
			if (exec->infile != -1)
				close(exec->infile);
			return (C_GEN);
		}
	}
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

	exec.pathname = NULL;
	exec.infile = -1;
	exec.outfile = -1;
	exec.pipes[0] = -1;
	exec.pipes[1] = -1;
	while (cmd)
	{
		if (find_element(*cmd, T_PIPE))
		{
			if (pipe(exec.pipes) == -1)
				return (-1);
			exec.outfile = exec.pipes[1];
		}
		if (fill_exec(&exec, *cmd, path) == C_GEN)
		{
			if (errno == C_NOEXEC)
				return (printf("No permission\n"), 127);
			else if (errno == C_NOFILE)
				return (printf("Not found\n"), 126);
		}
		if (init_redirect(cmd, &exec) == C_GEN)
			return (-1);
		pid = do_exec(&exec, NULL);
		(close(exec.infile), exec.infile = -1);
		(close(exec.outfile), exec.outfile = -1);
		cmd = find_element(*cmd, T_PIPE);
		if (cmd)
			exec.infile = exec.pipes[0];
	}
	waitpid(pid, NULL, 0);
	free(exec.pathname);
	return (0);
}
