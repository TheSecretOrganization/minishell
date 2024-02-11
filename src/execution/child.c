/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:26:42 by averin            #+#    #+#             */
/*   Updated: 2024/02/11 15:25:44 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Free execution
 * @param exec struct to free
*/
static void	free_exec(t_exec exec)
{
	free(exec.pathname);
	clean_data(exec.data);
	ft_fsplit(exec.data->path);
	ft_fsplit(exec.data->envp);
}

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
 * Duplicate fds to stdin and stdout
 * @param exec current execution informations
 * @return 0 or 1 if error
*/
static int	duplicate_fds(t_exec exec)
{
	int	infd;
	int	outfd;

	if (exec.infile != -1)
		infd = exec.infile;
	else
		infd = 0;
	if (exec.outfile != -1)
		outfd = exec.outfile;
	else
		outfd = 1;
	return (dup2(infd, STDIN_FILENO) == -1
		|| dup2(outfd, STDOUT_FILENO) == -1);
}

static void	handle_sigquit(int signal)
{
	(void)signal;
}

/**
 * Execute the command with the args and the env, redirect input and output
 * @param exec current execution informations
 * @param envp envp
 * @param int* where store the pid of the created child
*/
void	do_exec(t_exec *exec, char **envp, int *pid)
{
	if (exec->args[0] != NULL)
	{
		*pid = fork();
		if (*pid == -1)
			return (perror("fork"));
		else if (*pid == 0)
		{
			if (register_action(SIGQUIT, NULL, &handle_sigquit))
				(close_fds(exec), free_exec(*exec), exit(252));
			if (duplicate_fds(*exec))
				(perror("redirect error"), close_fds(exec), free_exec(*exec), \
				exit(254));
			close_fds(exec);
			if (execve(exec->pathname, exec->args, envp) == -1)
				(perror(exec->args[0]), free_exec(*exec), exit(253));
		}
	}
	if (exec->infile != -1)
		(close(exec->infile), exec->infile = -1);
	if (exec->outfile != -1)
		(close(exec->outfile), exec->outfile = -1);
}
