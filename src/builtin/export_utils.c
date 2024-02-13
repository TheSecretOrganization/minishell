/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:44:33 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/13 13:53:45 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Print the arg as export would
 *
 * @param arg
 * @param outfile
 */
void	print_export(char *arg, int outfile)
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

int	check_arg(char *arg, char **value)
{
	size_t	i;

	i = -1;
	*value = NULL;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (!arg[i] || arg[i] == '=')
		return (ft_dprintf(2, \
		"export: `%s': not a valid identifier\n", arg), C_GEN);
	if (arg[i] == '_' && (arg[i + 1] == '=' || arg[i + 1] == '\0'))
		return (-1);
	while (arg[++i])
	{
		printf("%ctest\n", arg[i]);
		if (arg[i] == '=')
		{
			*value = arg + i + 1;
			arg[i] = '\0';
			break ;
		}
		if (!ft_isalnum(arg[i]))
			return (ft_dprintf(2, \
			"export: `%s': not a valid identifier\n", arg), C_GEN);
	}
	return (C_SUCCESS);
}
