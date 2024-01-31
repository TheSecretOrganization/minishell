/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:08 by averin            #+#    #+#             */
/*   Updated: 2024/01/31 10:15:07 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#define SIZE_STEP 100

int	cmd_pwd(t_exec *exec)
{
	char	*cwd;
	size_t	size;

	if (exec->args[1] != NULL)
		return (ft_putstr_fd("pwd: too many arguments\n", 2), C_GEN);
	cwd = NULL;
	size = 0;
	while (!cwd)
	{
		size += SIZE_STEP;
		cwd = ft_calloc(size, sizeof(char));
		if (!cwd)
			return (C_MEM);
		if (!getcwd(cwd, size))
		{
			if (errno == ERANGE)
				(free(cwd), cwd = NULL);
			else
				return (free(cwd), perror("getcwd"), C_GEN);
		}
	}
	return (printf("%s\n", cwd), free(cwd), C_SUCCESS);
}
