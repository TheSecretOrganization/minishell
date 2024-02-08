/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:55:16 by averin            #+#    #+#             */
/*   Updated: 2024/02/08 11:24:01 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cmd_cd(t_exec *exec)
{
	char	*home;

	if (exec->is_pipe)
		return (C_SUCCESS);
	if (exec->args[1] == NULL)
	{
		home = ft_getenv(*exec->data, "HOME");
		if (!home)
			return (C_MEM);
		if (chdir(home) == -1)
			return (perror(home), free(home), C_GEN);
		return (free(home), C_SUCCESS);
	}
	if (chdir(exec->args[1]) == -1)
		return (perror(exec->args[1]), C_GEN);
	return (C_SUCCESS);
}
