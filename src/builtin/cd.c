/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:55:16 by averin            #+#    #+#             */
/*   Updated: 2024/02/12 09:55:50 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	free_cd(char *oldpwd, char *pwd, int fpwd)
{
	free(oldpwd);
	if (fpwd)
		free(pwd);
}

int	cmd_cd(t_exec *exec)
{
	char	*oldpwd;
	char	*pwd;
	int		code;

	if (exec->is_pipe)
		return (C_SUCCESS);
	code = ft_getcwd(&oldpwd);
	if (code != C_SUCCESS)
		return (code);
	code = 0;
	if (exec->args[1] == NULL && ++code)
	{
		pwd = ft_getenv(*exec->data, "HOME");
		if (!pwd)
			return (ft_dprintf(2, "HOME not set"), free(oldpwd), C_GEN);
	}
	else
		pwd = exec->args[1];
	if (chdir(pwd) == -1)
		return (perror(pwd), free_cd(oldpwd, pwd, code), C_GEN);
	if (ft_setenv(exec->data, "OLDPWD", oldpwd))
		return (free_cd(oldpwd, pwd, code), C_MEM);
	if (ft_setenv(exec->data, "PWD", pwd))
		return (free_cd(oldpwd, pwd, code), C_MEM);
	return (free_cd(oldpwd, pwd, code), C_SUCCESS);
}
