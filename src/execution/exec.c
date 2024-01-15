/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:41:06 by averin            #+#    #+#             */
/*   Updated: 2024/01/15 11:00:54 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/**
 * Execute a command
 * @param cmd command to execute
 * @param path environment's path
 * @return exit code
*/
int	exec_cmd(t_cmd *cmd, char **path)
{
	int	pid;

	pid = do_exec(exec, cmd->args, NULL, (int []){0, 1});
	waitpid(pid, NULL, 0);
	return (0);
}
