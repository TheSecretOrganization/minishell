/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:55:16 by averin            #+#    #+#             */
/*   Updated: 2024/02/01 23:07:13 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cmd_cd(t_exec *exec)
{
	if (exec->is_pipe)
		return (C_SUCCESS);
	if (exec->args[1] == NULL)
		return (C_BAD_USE);
	if (chdir(exec->args[1]) == -1)
		return (perror(exec->args[1]), C_GEN);
	return (C_SUCCESS);
}
