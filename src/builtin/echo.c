/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:16 by averin            #+#    #+#             */
/*   Updated: 2024/01/30 09:56:52 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cmd_echo(t_exec *exec)
{
	size_t	i;
	int		first;

	i = 0;
	first = 1;
	if (exec->args[0] == NULL)
		return (C_SUCCESS);
	if (ft_strncmp("-n", exec->args[1], 3) == 0)
		i++;
	while (exec->args[++i])
	{
		if (!first)
			ft_putstr_fd(" ", exec->outfile);
		ft_putstr_fd(exec->args[i], exec->outfile);
		first = 0;
	}
	if (ft_strncmp("-n", exec->args[1], 3) != 0)
		ft_putstr_fd("\n", exec->outfile);
	return (C_SUCCESS);
}
