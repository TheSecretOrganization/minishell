/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:55:16 by averin            #+#    #+#             */
/*   Updated: 2024/01/31 10:21:35 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cmd_cd(t_exec *exec)
{
	if (exec->args[1] == NULL)
		return (C_BAD_USE);
	if (chdir(exec->args[1]) == -1)
		return (perror(exec->args[1]), C_GEN);
	return (C_SUCCESS);
}
