/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:13:56 by averin            #+#    #+#             */
/*   Updated: 2024/01/30 09:28:36 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	check_files(t_exec *exec)
{
	if (exec->infile == -1)
		exec->infile = STDIN_FILENO;
	if (exec->outfile == -1)
		exec->outfile = STDOUT_FILENO;
}

static void	close_fds(t_exec *exec)
{
	if (exec->infile != STDIN_FILENO)
		(close(exec->infile), exec->infile = -1);
	if (exec->outfile != STDOUT_FILENO)
		(close(exec->outfile), exec->outfile = -1);
}

int	exec_builtin(t_exec *exec)
{
	int	code;

	check_files(exec);
	code = exec->builtin(exec);
	close_fds(exec);
	return (code);
}
