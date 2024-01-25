/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:41:06 by averin            #+#    #+#             */
/*   Updated: 2024/01/25 11:28:44 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/**
 * Open outfile and set corresponding fd in exec
 * @param cmd Command in wich search infile
 * @param exec Where to store infile fd
 * @return `C_SUCCESS` or `C_GEN` when error
*/
static int	init_outfile(t_cmd *cmd, t_exec *exec)
{
	t_outfile	*element;

	element = (t_outfile *) find_element(*cmd, T_OUTFILE);
	if (element != NULL)
	{
		if (element->outtype == OT_TRUNCATE)
			exec->outfile = open(element->filename,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (element->outtype == OT_APPEND)
			exec->outfile = open(element->filename,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (exec->outfile == -1)
			return (perror(element->filename), C_GEN);
	}
	return (C_SUCCESS);
}

/**
 * Open or create infile and set corresponding fd in exec
 * @param cmd Command in wich search infile
 * @param exec Where to store infile fd
 * @return `C_SUCCESS` or `C_GEN` when error
*/
static int	init_infile(t_cmd *cmd, t_exec *exec)
{
	t_infile	*element;

	element = (t_infile *) find_element(*cmd, T_INFILE);
	if (element != NULL)
	{
		if (element->intype == IT_INFILE)
			exec->infile = open(element->filename, O_RDONLY);
		else if (element->intype == IT_HERE_DOC)
			exec->infile = here_doc(element->filename);
		if (exec->infile == -1)
			return (perror(element->filename), C_GEN);
		else if (exec->infile == -2)
			return (C_BAD_USE);
	}
	return (C_SUCCESS);
}

/**
 * If the command have a pipe create it and store it in exec and close if 
 * another pipe is already open
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
 * @param envp current environment
 * @return exit code
*/
int	dispatch_cmd(t_cmd *cmd, char **path, char **envp)
{
	t_exec	exec;
	int		pid;
	t_code	err;

	init_exec(&exec);
	while (cmd)
	{
		if (init_pipe(cmd, &exec) == C_GEN)
			return (124);
		if (fill_exec(&exec, *cmd, path) == C_GEN)
		{
			if (errno == C_NOEXEC)
				return (printf("No permission\n"), 127);
			else if (errno == C_NOFILE)
				return (printf("Not found\n"), 126);
		}
		err = init_infile(cmd, &exec);
		if (err == C_BAD_USE)
			return (130);
		else if (err == C_GEN || init_outfile(cmd, &exec) == C_GEN)
			return (125);
		pid = do_exec(&exec, envp);
		cmd = find_element(*cmd, T_PIPE);
		if (cmd)
			exec.infile = exec.pipes[0];
	}
	free(exec.pathname);
	return (wait_children(pid));
}
