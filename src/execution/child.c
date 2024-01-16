/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:26:42 by averin            #+#    #+#             */
/*   Updated: 2024/01/16 10:38:12 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Close all opened fds
 * @param exec current exec status
*/
static void	close_fds(t_exec *exec)
{
	if (exec->infile != -1)
		(close(exec->infile), exec->infile = -1);
	if (exec->outfile != -1)
		(close(exec->outfile), exec->outfile = -1);
	if (exec->pipes[0] != -1)
		(close(exec->pipes[0]), exec->pipes[0] = -1);
	if (exec->pipes[1] != -1)
		(close(exec->pipes[1]), exec->pipes[1] = -1);
}

/**
 * Free execution
 * @param exec struct to free
*/
static void	free_exec(t_exec exec)
{
	free(exec.pathname);
	ft_fsplit(exec.args);
}

/**
 * Duplicate fds to stdin and stdout
 * @param infd fd to duplicate to stdin
 * @param outfd fd to duplicate to stdout
 * @return 0 or 1 if error
*/
static int	duplicate_fds(int infd, int outfd)
{
	if (infd == -1)
		infd = 0;
	if (outfd == -1)
		outfd = 1;
	return (dup2(infd, STDIN_FILENO) == -1
		|| dup2(outfd, STDOUT_FILENO) == -1);
}

/**
 * Execute the command with the args and the env, redirect input and output
 * @param exec executable path
 * @param args commands' args
 * @param envp envp
 * @param fds fd to redirect to {in, out}
 * @return execution's pid or -1
*/
int	do_exec(t_exec *exec, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	else if (pid == 0)
	{
		if (duplicate_fds(exec->infile, exec->outfile))
			(perror("redirect error"), close_fds(exec), free_exec(*exec), \
			exit(254));
		close_fds(exec);
		if (execve(exec->pathname, exec->args, envp) == -1)
			(perror("execution error"), free_exec(*exec), exit(253));
	}
	return (pid);
}
