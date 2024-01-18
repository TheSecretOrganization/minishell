/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/18 10:52:00 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Print syntax error for a special char error
 * @param code error code to return
 * @param line line that was parsed
 * @return t_code error code
*/
static t_code	error_ope(t_code code, char *line)
{
	if (!line)
		return (code);
	if (line + 1 && ft_strchr(CH_OPE, *(line + 1)) && \
	(*line == '|' || *(line + 1) == '&'))
		return (error_syntax(code, line, 2));
	return (error_syntax(code, line, 1));
}

/**
 * Check the syntax for special chars
 * @param line
 * @return t_code C_SUCCESS or C_BAD_USAGE
*/
static t_code	check_ope(char **line)
{
	char	c;
	size_t	i;

	c = **line;
	i = 0;
	while (*line && **line && ft_strchr(CH_OPE, **line) && ++i < 3)
	{
		if (c == '&' && **line != c)
			return (error_ope(C_BAD_USE, *line));
		(*line)++;
	}
	if (i >= 3)
		return (error_ope(C_BAD_USE, *line));
	return ((*line)--, C_SUCCESS);
}

/**
 * Check bash syntax in one line
 * @param line line to check
 * @return t_code C_SUCCESS or C_BAD_USE
*/
static t_code	check_syntax(char *line)
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
		if (!(nq % 2) && !(nd % 2) && ft_strchr(CH_OPE, *line) \
		&& check_ope(&line))
			return (C_BAD_USE);
		line++;
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}

/**
 * Parse user's input, exit the program if error occurs
 * @param cmd list of comamnd to init
 * @param line line to parse
 * @return t_code C_SUCCESS or an error code
*/
t_code	parse_line(t_cmd **cmd, char *line)
{
	if (check_syntax(line))
		return (C_BAD_USE);
	return (C_SUCCESS);
}
