/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:44:33 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/13 17:21:56 by abasdere         ###   ########.fr       */
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

/**
 * @brief Check argument for export
 *
 * @param arg argument to check
 * @param value pointer on where to store the value
 * @return int
 */
int	check_arg(char *arg, char **value)
{
	size_t	i;

	i = -1;
	*value = NULL;
	if (!arg[0] || arg[0] == '=')
		return (ft_dprintf(2, \
		"export: `%s': not a valid identifier\n", arg), C_GEN);
	if (arg[0] == '_' && (arg[1] == '=' || arg[1] == '\0'))
		return (-1);
	while (arg[++i])
	{
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
