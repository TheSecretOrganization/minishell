/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:54:29 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/20 16:45:42 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	is_only_ope_or_sep(char *line, char *start)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = -1;
	while (line && line[++i])
		if (line[i] != ' ' && !ft_strchr(CH_OPE, line[i]) && ++nb)
			break ;
	while (line != start)
	{
		if (*line != ' ' && !ft_strchr(CH_OPE, *line) && ++nb)
			break ;
		line--;
	}
	if (nb == 2)
		return (B_FALSE);
	return (B_TRUE);
}

/**
 * Check the syntax for special chars
 * @param line pointer to the line to check
 * @param start start of the line to check
 * @return t_code C_SUCCESS or C_BAD_USAGE
*/
static t_code	check_ope(char **line, char *start)
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
	if (is_only_ope_or_sep(*line - i, start))
		return (error_syntax(C_BAD_USE, *line - i, i));
	return ((*line)--, C_SUCCESS);
}

static t_bool	is_only_dir_or_sep(char *line)
{
	while (line && *line)
	{
		if (*line != ' ' && !ft_strchr(CH_DIR, *line))
			return (B_FALSE);
		line++;
	}
	return (B_TRUE);
}

static	t_bool	check_diff_dir(char **line, char c)
{
	size_t	i;

	i = -1;
	(*line)++;
	while (*line && **line && ft_strchr(CH_DIR, **line) && ++i)
	{
		if (**line != *(*line + 1))
			break ;
		(*line)++;
	}
	if (c == '<')
	{

	}
	else if (c == '>')
	{

	}
	return (C_SUCCESS);
}

/**
 * Check the syntax for redirection chars
 * @param line
 * @return t_code C_SUCCESS or C_BAD_USAGE
*/
static t_code	check_dir(char **line)
{
	char	c;
	size_t	i;

	c = **line;
	i = 0;
	while (*line && **line == c && ++i)
		(*line)++;
	if (ft_strchr(CH_DIR, *(*line + 1)) && check_diff_dir(line, c))
		return (C_BAD_USE);
	if ((c == '<' && i > 3))
	{
		if (i - 3 > 3)
			return (error_syntax(C_BAD_USE, *line - (i - 3), 3));
		return (error_syntax(C_BAD_USE, *line - (i - 3), i - 3));
	}
	else if ((c == '>' && i > 2))
	{
		if (i - 2 > 2)
			return (error_syntax(C_BAD_USE, *line - (i - 2), 2));
		return (error_syntax(C_BAD_USE, *line - (i - 2), i - 2));
	}
	if (is_only_dir_or_sep(*line))
		return (error_syntax(C_BAD_USE, NULL, 0));
	return ((*line)--, C_SUCCESS);
}

/**
 * Check bash syntax in one line
 * @param line line to check
 * @param start start of line
 * @return t_code C_SUCCESS or C_BAD_USE
*/
t_code	check_syntax(char *line, char *start)
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
		if (!(nq % 2) && !(nd % 2)
			&& ((ft_strchr(CH_OPE, *line) && check_ope(&line, start))
				|| (ft_strchr(CH_DIR, *line) && check_dir(&line))))
			return (C_BAD_USE);
		line++;
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}
