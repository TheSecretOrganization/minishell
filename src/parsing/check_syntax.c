/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:54:29 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/23 11:09:32 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Write error statement to stderr
 * @param code exit code to return
 * @param el element which caused the error, nullable
 * @param n number of char from el to print
 * @return t_code error code
*/
t_code	error_syntax(t_code code, char *el, size_t n)
{
	size_t	i;

	i = -1;
	ft_putstr_fd("minishell: syntax error near unexpected token `", \
	STDERR_FILENO);
	if (el)
		while (*el && ++i < n)
			ft_putchar_fd(*(el++), STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	return (code);
}

/**
 * Check bash syntax in one line
 * @param line line to check
 * @return t_code C_SUCCESS or C_BAD_USE
*/
t_code	check_syntax(char *line)
{
	size_t	nq;
	size_t	nd;

	nq = 0;
	nd = 0;
	while (line && *line)
	{
		if (*line == '\'' && !(nd % 2))
			nq++;
		if (*line == '\"' && !(nq % 2))
			nd++;
		if (!(nq % 2) && !(nd % 2) && ft_strchr(CH_ERR, *line))
			return (error_syntax(C_BAD_USE, line, 1));
		line++;
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}
