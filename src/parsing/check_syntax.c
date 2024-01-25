/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:54:29 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/25 16:50:30 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
 * @brief Check if all quotes are closed in the line
 *
 * @param line line to parse
 * @return t_code C_SUCCESS or an error
 */
t_code	check_quotes(char *line)
{
	size_t	nq;
	size_t	nd;
	size_t	i;

	nq = 0;
	nd = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' && !(nd % 2))
			nq++;
		if (line[i] == '\"' && !(nq % 2))
			nd++;
		if (!(nq % 2) && !(nd % 2) && ft_strchr(CH_ERR, line[i]))
			return (error_syntax(C_BAD_USE, &(line[i]), 1));
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}

/**
 * @brief Check pipe syntax in line
 *
 * @param line line to check
 * @param pos position in line
 * @return t_code C_SUCCESS or an error
 */
t_code	check_pipe(char *line, size_t pos)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = pos;
	if (line[pos + 1] == '&')
		return (error_syntax(C_BAD_USE, line + pos, 2));
	while (line[pos + nb] == '|' || line[pos + nb] == '&')
		nb++;
	if (nb == 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 1));
	if (nb > 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 2));
	if (pos && i--)
		while (i > 0 && line[i] != '|' && !ft_isalnum(line[i]))
			i--;
	if (!i && !ft_isalnum(line[i]))
		return (error_syntax(C_BAD_USE, line + pos, nb));
	i = pos + 1;
	while (line[i] && line[i] != '|' && !ft_isalnum(line[i]))
		i++;
	if (!line[i])
		return (error_syntax(C_BAD_USE, line + pos, nb));
	return (C_SUCCESS);
}

/**
 * @brief Check special chars syntax in line
 *
 * @param line line to check
 * @return t_code C_SUCCESS or an error
 */
t_code	check_spcl_chars(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && check_pipe(line, i))
			return (C_BAD_USE);
	}
	return (C_SUCCESS);
}

/**
 * Check bash syntax in one line
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or C_BAD_USE
*/
t_code	check_syntax(t_data *data)
{
	if (check_quotes(data->line))
		return (C_BAD_USE);
	if (check_spcl_chars(data->line))
		return (C_BAD_USE);
	data->line = expand_variables(data->line, data->status);
	if (!data->line)
		return (C_MEM);
	return (C_SUCCESS);
}
