/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:08 by averin            #+#    #+#             */
/*   Updated: 2024/02/12 10:04:51 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#define SIZE_STEP 100

/**
 * @brief Get the current working directory
 *
 * @param cwd pointer on where to store the cwd
 * @return int C_SUCCES or an error
 */
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

/**
 * @brief Reproduce the behaviour of pwd
 *
 * @param exec data of the program
 * @return int C_SUCCES or an error
 */
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
