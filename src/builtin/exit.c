/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:37:58 by averin            #+#    #+#             */
/*   Updated: 2024/02/08 09:38:32 by abasdere         ###   ########.fr       */
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
	int		code;
	char	*tmp;

	code = C_SUCCESS;
	if (!exec->is_pipe)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (exec->args[1] && exec->args[2])
		return (printf("exit: too many arguments\n"), 1);
	else if (exec->args[1])
	{
		code = ft_atoi(exec->args[1]);
		tmp = ft_itoa(code);
		if (!tmp)
			return (C_MEM);
		if (ft_strncmp(exec->args[1], tmp, ft_strlen(exec->args[1])))
			(printf("exit: %s: numeric argument required\n", exec->args[1]), \
			code = 2);
		free(tmp);
	}
	if (exec->is_pipe)
		return (code);
	(close_fds(exec), ft_fsplit(exec->data->envp), clean_data(exec->data));
	exit(code);
}
