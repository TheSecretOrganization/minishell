/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:12 by averin            #+#    #+#             */
/*   Updated: 2024/02/07 14:43:19 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Swap s1 and s2
 *
 * @param s1
 * @param s2
 */
static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

/**
 * @brief Quick sort the envp
 *
 * @param envp
 * @param len
 */
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

/**
 * @brief Print the arg as export would
 *
 * @param arg
 * @param outfile
 */
static void	print_export(char *arg, int outfile)
{
	t_bool	eql;
	size_t	i;

	eql = B_FALSE;
	if (arg[0] == '_' && (arg[1] == '=' || arg[1] == '\0'))
		return ;
	(ft_putstr_fd("export ", outfile), i = -1);
	while (arg[++i])
	{
		if (arg[i] == '=')
			(ft_putstr_fd("=\"", outfile), eql = B_TRUE);
		else if (arg[i] == '\"')
			(ft_putchar_fd('\\', outfile), ft_putchar_fd(arg[i], outfile));
		else
			ft_putchar_fd(arg[i], outfile);
	}
	if (eql)
		ft_putchar_fd('\"', outfile);
	ft_putchar_fd('\n', outfile);
}

/**
 * @brief Process the arg to modify the envp
 *
 * @param arg
 * @param data
 * @return int
 */
static int	process_arg(char *arg, t_data *data)
{
	char	*value;
	int		code;

	if (arg[0] == '_' && (arg[1] == '=' || arg[1] == '\0'))
		return (C_SUCCESS);
	value = ft_strchr(arg, '=');
	if (value)
		*(value++) = '\0';
	code = ft_setenv(data, arg, value);
	if (value)
		*(--value) = '=';
	if (!code && !ft_strncmp(arg, "PATH", 4)
		&& (arg[4] == '\0' || arg[4] == '='))
		return (get_path(data));
	return (code);
}

/**
 * @brief Reproduce the behaviour of export builtin
 *
 * @param exec data of the execution branch
 * @return int
 */
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
			print_export(cpy.envp[i++], exec->outfile);
		return (ft_fsplit(cpy.envp), C_SUCCESS);
	}
	while (exec->args[++i])
		if (process_arg(exec->args[i], exec->data))
			return (C_MEM);
	return (C_SUCCESS);
}
