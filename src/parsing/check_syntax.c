/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:54:29 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/24 09:41:58 by abasdere         ###   ########.fr       */
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
 * @brief check if the line contains only chars from a set
 *
 * @param line current position in line parsed
 * @param start start of line parsed
 * @param set set of special chars to check
 * @return t_bool
 */
static t_bool	check_only_set(char *line, char *start, char *set)
{
	t_bool	checks[2];
	size_t	i;

	checks[0] = B_TRUE;
	checks[1] = B_TRUE;
	i = -1;
	while (line[++i] && checks[0] == B_TRUE)
		if (!ft_strchr(set, line[i]))
			checks[0] = B_FALSE;
	if (start)
	{
		while (start != line && checks[1] == B_TRUE)
			if (!ft_strchr(set, *(line++)))
				checks[1] = B_FALSE;
		if (checks[0] == B_FALSE && checks[1] == B_FALSE)
			return (B_FALSE);
		else
			return (B_TRUE);
	}
	return (checks[0]);
}

/**
 * @brief Check bash special chars syntax
 *
 * @param line pointer on the current position in the line parsed
 * @param start start of the line parsed
 * @return t_code C_SUCCES or an error
 */
static t_code	check_special_chars(char **line, char *start)
{
	if (ft_strchr(CH_DIR, **line) && check_dir(line))
		return (C_BAD_USE);
	else if (ft_strchr(CH_OPE, **line) && check_ope(line, start))
		return (C_BAD_USE);
	return (C_SUCCESS);
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
	char	*start;

	nq = 0;
	nd = 0;
	start = line;
	while (line && *line)
	{
		if (*line == '\'' && !(nd % 2))
			nq++;
		if (*line == '\"' && !(nq % 2))
			nd++;
		if (!(nq % 2) && !(nd % 2) && ft_strchr(CH_ERR, *line))
			return (error_syntax(C_BAD_USE, line, 1));
		if (check_special_chars(&line, start))
			return (C_BAD_USE);
		line++;
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}
