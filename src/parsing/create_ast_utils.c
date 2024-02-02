/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/01 20:01:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Catenate a space and n char from one string to another
 * @param s1 destination string, will be free
 * @param s2 source string
 * @param n number of char to catenate
 * @return char * or NULL if an error occurs
*/
static char	*fspace_njoin(char *s1, char *s2, size_t n)
{
	size_t	len;
	size_t	i;
	char	*join;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	join = ft_calloc(len + n + 2, sizeof(char));
	if (!join)
		return (free(s1), s1 = NULL, error(C_MEM, "ft_calloc", M_MEM), NULL);
	i = -1;
	while (++i < len)
		join[i] = s1[i];
	join[len] = ' ';
	i = -1;
	while (++i < n)
		join[len + 1 + i] = s2[i];
	return (free(s1), s1 = NULL, join);
}

/**
 * Join the new argument argument with the joined ones
 * @param ast pointer on the control structure
 * @param line line parsed
 * @return t_code C_SUCCES or an error
*/
t_code	join_args(t_ast *ast, char *line)
{
	if (!ast || !line)
		return (error(C_BAD_USE, "join_args", M_ERROR));
	ast->j_args = fspace_njoin(ast->j_args, line \
	+ ast->i, ast->next - &(line[ast->i]));
	if (!ast->j_args)
		return (error(C_MEM, "fspace_njoin", M_MEM));
	return (ast->i = ast->next - &(line[0]), C_SUCCESS);
}

/**
 * Split the arguments of a command
 * @param ast pointer on the control structure
 * @return t_code C_SUCCESS or an error
*/
t_code	split_args(t_ast *ast)
{
	if (!ast || !ast->target || !ast->j_args)
		return (C_BAD_USE);
	ast->target->args = ft_split(ast->j_args, ' ');
	(free(ast->j_args), ast->j_args = NULL);
	if (!ast->target->args)
		return (error(C_MEM, "ft_split", M_MEM));
	return (C_SUCCESS);
}

/**
 * Find the next separator in a line
 * @param line line to check
 * @return char * to the next seprator
*/
char	*find_next_sep(char *line)
{
	if (!line)
		return (NULL);
	while (*line)
	{
		if (ft_strchr(CH_SPCL, *line) || *line == ' ')
			return (line);
		line++;
	}
	return (line);
}

char	*find_next_arg(char *line, char **end)
{
	while (*line && (*line == ' ' || ft_strchr(CH_SPCL, *line)))
		line++;
	if (!*line)
		return (*end = line, line);
	*end = line + 1;
	while (**end && **end != ' ' && !ft_strchr(CH_SPCL, **end))
		(*end)++;
	return (line);
}
