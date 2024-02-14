/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:54:29 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/14 16:52:20 by abasdere         ###   ########.fr       */
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
	ft_putstr_fd("Syntax error near unexpected token `", STDERR_FILENO);
	if (el)
		while (*el && ++i < n)
			ft_putchar_fd(*(el++), STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	return (code);
}

/**
 * @brief Check if the here_doc delimiter has quotes
 *
 * @param line line to parse
 * @param i pointer on the position in line
 * @return int B_TRUE
 */
static int	check_hd(char *line, size_t *i)
{
	*i += 2;
	while (line[*i] && ft_is_space(line[*i]))
		(*i)++;
	if (line[*i] != '\'' && line[*i] != '\"')
		return (*i -= 1, B_TRUE);
	while (line[*i] && !ft_is_space(line[*i]) && !ft_strchr(CH_SPCL, line[*i]))
		(*i)++;
	return (*i -= 1, B_TRUE);
}

/**
 * @brief Remove outer quotes from a line
 *
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or an error
 */
t_code	expand(t_data *data)
{
	size_t	nq;
	size_t	nd;
	size_t	i;

	nq = 0;
	nd = 0;
	i = -1;
	while (data->line[++i])
	{
		if (data->line[i] == '<' && data->line[i + 1] == '<'
			&& check_hd(data->line, &i))
			continue ;
		if (!(nq % 2) && ((data->line[i]) == '~' || data->line[i] == '$'))
			if (expand_var(data, &i, nd))
				return (C_MEM);
		if (data->line[i] == '\'' && !(nd % 2))
			nq++;
		else if (data->line[i] == '\"' && !(nq % 2))
			nd++;
	}
	return (C_SUCCESS);
}

/**
 * @brief Check if all quotes are closed in the line
 *
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or an error
 */
t_code	check_quotes(t_data *data)
{
	size_t	nq;
	size_t	nd;
	size_t	i;

	nq = 0;
	nd = 0;
	i = -1;
	while (data->line[++i])
	{
		if (!(nq % 2) && !(nd % 2) && ft_strchr(CH_ERR, data->line[i]))
			return (error_syntax(C_BAD_USE, &(data->line[i]), 1));
		if (data->line[i] == '\'' && !(nd % 2))
			nq++;
		if (data->line[i] == '\"' && !(nq % 2))
			nd++;
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}

/**
 * Check bash syntax in one line
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or C_BAD_USE
*/
t_code	check_syntax(t_data *data)
{
	if (check_quotes(data) || check_spcl_chars(data->line))
		return (C_BAD_USE);
	return (C_SUCCESS);
}
