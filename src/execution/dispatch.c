/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:41:06 by averin            #+#    #+#             */
/*   Updated: 2024/01/22 11:37:38 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/**
 * Open infile and set corresponding fd in exec
 * @param cmd Command in wich search infile
 * @param exec Where to store infile fd
 * @return `C_SUCCESS` or `C_GEN` when error
*/
static int	init_outfile(t_cmd *cmd, t_exec *exec)
{
	void	*element;

	element = find_element(*cmd, T_OUTFILE);
	if (element != NULL)
	{
		if (exec->pipes[0] != -1)
			(close(exec->pipes[0]), exec->pipes[0] = -1);
		exec->outfile = open(element, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (exec->outfile == -1)
			return (perror(element), C_GEN);
	}
	return (C_SUCCESS);
}

/**
 * Open or create outfile and set corresponding fd in exec
 * @param cmd Command in wich search infile
 * @param exec Where to store infile fd
 * @return `C_SUCCESS` or `C_GEN` when error
*/
static int	init_infile(t_cmd *cmd, t_exec *exec)
{
	void	*element;

	element = find_element(*cmd, T_INFILE);
	if (element != NULL)
	{
		if (exec->pipes[1] != -1)
			(close(exec->pipes[1]), exec->pipes[1] = -1);
		exec->infile = open(element, O_RDONLY);
		if (exec->infile == -1)
			return (perror(element), C_GEN);
	}
	return (C_SUCCESS);
}

/**
 * If the command have a pipe create it and store it in exec
 * @param cmd Where search for pipe
 * @param exec Where store thie pipe
 * @return `C_SUCCESS` or `C_GEN` when error
*/
static int	init_pipe(t_cmd *cmd, t_exec *exec)
{
	if (find_element(*cmd, T_PIPE))
	{
		if (pipe(exec->pipes) == -1)
			return (perror("pipe"), C_GEN);
		exec->outfile = exec->pipes[1];
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

	init_exec(&exec);
	while (cmd)
	{
		if (init_pipe(cmd, &exec) == C_GEN)
			return (-1);
		if (fill_exec(&exec, *cmd, path) == C_GEN)
		{
			if (errno == C_NOEXEC)
				return (printf("No permission\n"), 127);
			else if (errno == C_NOFILE)
				return (printf("Not found\n"), 126);
		}
		if (init_infile(cmd, &exec) == C_GEN
			|| init_outfile(cmd, &exec) == C_GEN)
			return (-1);
		pid = do_exec(&exec, NULL);
		cmd = find_element(*cmd, T_PIPE);
		if (cmd)
			exec.infile = exec.pipes[0];
	}
	(waitpid(pid, NULL, 0), free(exec.pathname));
	return (0);
}
