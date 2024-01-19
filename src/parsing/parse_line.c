/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/19 14:36:18 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	while (*line && **line && ft_strchr(CH_OPE, **line) && ++i)
	{
		if (i <= 2 && **line != c)
			return (error_syntax(C_BAD_USE, *line, 1));
		(*line)++;
	}
	if ((c == '&' && i == 1) || i == 3)
		return (error_syntax(C_BAD_USE, *line - 1, 1));
	else if (i > 3)
	{
		*line -= (i - 2);
		if (**line == '|' || **line == *(*line + 1))
			return (error_syntax(C_BAD_USE, *line, 2));
		return (error_syntax(C_BAD_USE, *line, 1));
	}
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
	if (!line || !*line)
		return (C_SUCCESS);
	if (check_syntax(line))
		return (C_BAD_USE);
	if (create_cmd(cmd, line))
		return (C_BAD_USE);
	return (C_SUCCESS);
}
