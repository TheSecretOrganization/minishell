/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:12 by averin            #+#    #+#             */
/*   Updated: 2024/02/06 16:07:11 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void	quicksort(char **envp, size_t len)
{
	size_t	i;
	size_t	piv;

	i = -1;
	piv = 0;
	if (len <= 1)
		return ;
	while (++i < len)
		if (ft_strncmp(envp[i], envp[len -1], ft_strlen(envp[i])) < 0)
			swap(envp + i, envp + piv++);
	swap(envp + piv, envp + len - 1);
	quicksort(envp, piv++);
	quicksort(envp + piv, len - piv);
}

static void	print_export(char *arg)
{
	t_bool	eql;
	size_t	i;

	eql = B_FALSE;
	(ft_putstr_fd("export ", 1), i = -1);
	while (arg[++i])
	{
		if (arg[i] == '=')
			(ft_putstr_fd("=\"", 1), eql = B_TRUE);
		else if (arg[i] == '\"')
			(ft_putchar_fd('\\', 1), ft_putchar_fd(arg[i], 1));
		else
			ft_putchar_fd(arg[i], 1);
	}
	if (eql)
		ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}

static int	process_arg(char *arg, t_data *data)
{
	char	*value;
	int		code;

	value = ft_strchr(arg, '=');
	if (value)
		*(value++) = '\0';
	code = ft_setenv(data, arg, value);
	if (value)
		*(--value) = '=';
	return (code);
}

int	cmd_export(t_exec *exec)
{
	size_t	i;
	t_data	cpy;

	i = 0;
	if (exec->is_pipe || exec->args[0] == NULL)
		return (C_SUCCESS);
	else if (exec->args[1] == NULL)
	{
		if (cpy_envp(&cpy, exec->data->envp))
			return (C_MEM);
		while (cpy.envp[i])
			i++;
		(quicksort(cpy.envp, i), i = 0);
		while (cpy.envp[i])
			print_export(cpy.envp[i++]);
		ft_fsplit(cpy.envp);
	}
	else
		while (exec->args[++i])
			if (process_arg(exec->args[i], exec->data))
				return (C_MEM);
	return (C_SUCCESS);
}
