/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:08 by averin            #+#    #+#             */
/*   Updated: 2024/02/12 09:37:46 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#define SIZE_STEP 100

int	ft_getcwd(char **cwd)
{
	size_t	size;

	*cwd = NULL;
	size = 0;
	while (!*cwd)
	{
		size += SIZE_STEP;
		*cwd = ft_calloc(size, sizeof(char));
		if (!*cwd)
			return (C_MEM);
		if (!getcwd(*cwd, size))
		{
			if (errno == ERANGE)
				(free(*cwd), *cwd = NULL);
			else
				return (free(*cwd), perror("getcwd"), C_GEN);
		}
	}
	return (C_SUCCESS);
}

int	cmd_pwd(t_exec *exec)
{
	char	*cwd;
	int		code;

	if (exec->args[1] != NULL)
		return (ft_putstr_fd("pwd: too many arguments\n", 2), C_GEN);
	code = ft_getcwd(&cwd);
	if (code != C_SUCCESS)
		return (code);
	return (printf("%s\n", cwd), free(cwd), C_SUCCESS);
}
