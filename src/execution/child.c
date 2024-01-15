/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:26:42 by averin            #+#    #+#             */
/*   Updated: 2024/01/15 11:06:52 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Execute the command with the args and the env, redirect input and output
 * @param exec executable path
 * @param args commands' args
 * @param envp envp
 * @param fds fd to redirect to {in, out}
 * @return execution's pid or -1
*/
int	do_exec(char *exec, char **args, char **envp, int *fds)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	else if (pid == 0)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1
			|| dup2(fds[1], STDOUT_FILENO) == -1)
			(perror("redirect error"), exit(254));
		(close(fds[0]), close(fds[1]));
		if (execve(exec, args, envp) == -1)
			(perror("execution error"), exit(253));
	}
	return (pid);
}
