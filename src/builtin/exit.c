/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:37:58 by averin            #+#    #+#             */
/*   Updated: 2024/02/01 22:31:08 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	close_fds(t_exec *exec)
{
	if (exec->infile != STDIN_FILENO)
		(close(exec->infile), exec->infile = -1);
	if (exec->outfile != STDOUT_FILENO)
		(close(exec->outfile), exec->outfile = -1);
}

int	cmd_exit(t_exec *exec)
{
	if (exec->is_pipe)
		return (C_SUCCESS);
	(close_fds(exec), clean_data(exec->data));
	(ft_putendl_fd("exit", STDOUT_FILENO), exit(C_SUCCESS));
}
