/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:13:56 by averin            #+#    #+#             */
/*   Updated: 2024/02/14 22:30:49 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin.h"

static int	cmp_cmd(char *name, char *cmd)
{
	return (ft_strncmp(name, cmd, ft_strlen(name) + 1));
}

static void	set_cmd(t_exec *exec, int (*f)(t_exec *))
{
	exec->is_builtin = 1;
	exec->builtin = f;
}

int	exec_builtin(t_exec *exec)
{
	int	code;

	if (exec->infile == -1)
		exec->infile = STDIN_FILENO;
	if (exec->outfile == -1)
		exec->outfile = STDOUT_FILENO;
	code = exec->builtin(exec);
	return (code);
}

int	is_builtin(t_cmd cmd, t_exec *exec)
{
	char	*name;

	if (!cmd.args)
		return (FALSE);
	name = cmd.args[0];
	if (!cmp_cmd(name, "echo"))
		set_cmd(exec, cmd_echo);
	if (!cmp_cmd(name, "cd"))
		set_cmd(exec, cmd_cd);
	if (!cmp_cmd(name, "pwd"))
		set_cmd(exec, cmd_pwd);
	if (!cmp_cmd(name, "export"))
		set_cmd(exec, cmd_export);
	if (!cmp_cmd(name, "unset"))
		set_cmd(exec, cmd_unset);
	if (!cmp_cmd(name, "env"))
		set_cmd(exec, cmd_env);
	if (!cmp_cmd(name, "exit"))
		set_cmd(exec, cmd_exit);
	return (exec->is_builtin);
}
