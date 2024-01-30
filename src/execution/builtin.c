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

int	exec_builtin(t_exec *exec)
{
	check_files(exec);
	return (exec->builtin(exec));
}
