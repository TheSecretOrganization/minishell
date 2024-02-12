/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:55:16 by averin            #+#    #+#             */
/*   Updated: 2024/02/12 11:00:31 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_setpwd(char **pwd, char *arg, t_data data)
{
	int		code;

	code = C_SUCCESS;
	if (arg == NULL)
	{
		*pwd = ft_getenv(data, "HOME");
		if (!*pwd)
			return (ft_dprintf(2, "HOME not set\n"), C_GEN);
	}
	else if (arg[0] != '/')
	{
		code = ft_getcwd(pwd);
		if (code)
			return (code);
		*pwd = ft_fstrjoin(*pwd, "/", 1);
		if (!*pwd)
			return (C_MEM);
		*pwd = ft_fstrjoin(*pwd, arg, 1);
	}
	else
		*pwd = ft_strdup(arg);
	if (!*pwd)
		return (C_MEM);
	return (C_SUCCESS);
}

/**
 * @brief Reproduce the behaviour of cd
 *
 * @param exec data of the program
 * @return int C_SUCCES or an error
 */
int	cmd_cd(t_exec *exec)
{
	char	*oldpwd;
	char	*pwd;
	int		code;

	if (exec->is_pipe)
		return (C_SUCCESS);
	if (exec->args[1] && exec->args[2])
		return (ft_dprintf(2, "cd: too many arguments\n"), C_GEN);
	oldpwd = ft_getenv(*exec->data, "PWD");
	if (!oldpwd)
		return (C_GEN);
	code = ft_setpwd(&pwd, exec->args[1], *(exec->data));
	if (code)
		return (free(oldpwd), code);
	if (chdir(pwd) == -1)
		return (perror(pwd), free(oldpwd), free(pwd), C_GEN);
	(free(pwd), code = ft_getcwd(&pwd));
	if (code)
		return (free(oldpwd), free(pwd), code);
	if (ft_setenv(exec->data, "PWD", pwd))
		return (free(oldpwd), free(pwd), C_MEM);
	if (ft_setenv(exec->data, "OLDPWD", oldpwd))
		return (free(oldpwd), free(pwd), C_MEM);
	return (free(oldpwd), free(pwd), C_SUCCESS);
}
