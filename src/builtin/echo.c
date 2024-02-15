/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:16 by averin            #+#    #+#             */
/*   Updated: 2024/02/15 08:57:04 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	has_n_args(char *arg)
{
	size_t	i;

	if (arg[0] != '-')
		return (FALSE);
	i = 0;
	while (arg[++i] == 'n')
		;
	return (arg[i] == '\0');
}

int	cmd_echo(t_exec *exec)
{
	size_t	i;
	int		first;

	i = 0;
	first = 1;
	if (write(exec->outfile, "", 0) == -1)
		return (perror("echo"), C_GEN);
	if (exec->args[1] == NULL)
		return (ft_putstr_fd("\n", exec->outfile), C_SUCCESS);
	while (exec->args[++i] && has_n_args(exec->args[i]))
		;
	i--;
	while (exec->args[++i])
	{
		if (!first)
			ft_putstr_fd(" ", exec->outfile);
		ft_putstr_fd(exec->args[i], exec->outfile);
		first = 0;
	}
	if (!has_n_args(exec->args[1]))
		ft_putstr_fd("\n", exec->outfile);
	return (C_SUCCESS);
}
