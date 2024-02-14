/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/14 18:08:38 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Remove outer quotes from a line
 *
 * @param s pointer on the string to trim
 * @param d of the program, nullable
 * @param expand boolean to expand or not
 */
int	remove_quotes(char **s, t_data *d, int expand)
{
	size_t	nq;
	size_t	nd;
	size_t	i;

	nd = 0;
	nq = 0;
	i = -1;
	while ((*s)[++i])
	{
		if ((!(nq % 2) && !(nd % 2) && ft_is_space((*s)[i]))
			|| (nq % 2 && (*s)[i] == '\'') || (nd % 2 && (*s)[i] == '\"'))
			expand = 0;
		if (d && !(nq % 2) && ((d->line[i]) == '~' || d->line[i] == '$'))
		{
			if (++expand && expand_var(d, i, nd))
				return (C_MEM);
			i--;
			continue ;
		}
		if (!expand && (*s)[i] == '\'' && !(nd % 2) && ++nq)
			(ft_memcpy(&((*s)[i]), &((*s)[i + 1]), ft_strlen((*s)) - i), i--);
		else if (!expand && (*s)[i] == '\"' && !(nq % 2) && ++nd)
			(ft_memcpy(&((*s)[i]), &((*s)[i + 1]), ft_strlen((*s)) - i), i--);
	}
	return (C_SUCCESS);
}

/**
 * @brief Find the next argument in line
 *
 * @param line line to parse
 * @param end pointer on the end of the arg
 * @return char* start of the next arg
 */
static char	*find_next_arg(char *line, char **end)
{
	char	c;

	c = '\0';
	while (*line && ft_is_space(*line))
		line++;
	if (!*line)
		return (*end = line, line);
	*end = line;
	if (**end != '\0' && ft_strchr(CH_SPCL, *line))
		while (**end != '\0' && ft_strchr(CH_SPCL, **end))
			(*end)++;
	else
	{
		while (**end != '\0' && !ft_strchr(CH_SPCL, **end))
		{
			if (!c && (**end == '\'' || **end == '\"'))
				c = **end;
			else if (c && **end == c)
				c = '\0';
			if (!c && ft_is_space(**end))
				break ;
			(*end)++;
		}
	}
	return (line);
}

/**
 * @brief Get the next substr object
 *
 * @param ast pointer on the top of the ast
 * @param line line parsed
 * @return char* or NULL
 */
char	*get_next_substr(t_ast *ast, char *line)
{
	char	*sub;
	char	*start;
	char	*end;

	start = find_next_arg(line + ast->i, &end);
	sub = ft_substr(line, start - line, end - start);
	if (!sub)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	return (ast->new_i = end, sub);
}
