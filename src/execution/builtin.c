/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:13:56 by averin            #+#    #+#             */
/*   Updated: 2024/01/29 09:31:19 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	check_files(t_exec *exec)
{
	if (exec->infile == -1)
		exec->infile = 1;
	if (exec->outfile == -1)
		exec->outfile = 0;
}

int	exec_builtin(t_exec *exec)
{
	check_files(exec);
	return (exec->builtin(exec));
}
