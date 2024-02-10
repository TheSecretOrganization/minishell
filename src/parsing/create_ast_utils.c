/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/10 12:35:52 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Remove outer quotes from a line
 *
 * @param s pointer on the string to trim
 */
void	remove_quotes(char **s)
{
	size_t	nq;
	size_t	nd;
	size_t	i;

	nq = 0;
	nd = 0;
	i = -1;
	while ((*s)[++i])
	{
		if ((*s)[i] == '\'' && !(nd % 2) && ++nq)
			(ft_memcpy(&((*s)[i]), &((*s)[i + 1]), \
			ft_strlen((*s)) - i), i--);
		else if ((*s)[i] == '\"' && !(nq % 2) && ++nd)
			(ft_memcpy(&((*s)[i]), &((*s)[i + 1]), \
			ft_strlen((*s)) - i), i--);
	}
}

/**
 * Join the new argument argument with the joined ones
 * @param ast pointer on the control structure
 * @param line line parsed
 * @return t_code C_SUCCES or an error
*/
t_code	add_arg(t_ast *ast, char *line)
{
	char	**new;
	size_t	len;

	remove_quotes(&(ast->next));
	len = 0;
	while (ast->target->args[len])
		len++;
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (ft_fsplit(ast->target->args), free(ast->next), C_MEM);
	len = -1;
	while (ast->target->args[++len])
		new[len] = ast->target->args[len];
	new[len] = ast->next;
	(free(ast->target->args), ast->target->args = new);
	return (ast->i = ast->new_i - line, C_SUCCESS);
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

	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (*end = line, line);
	c = *line;
	*end = line + 1;
	if (c == '\"' || c == '\'')
	{
		while (**end && **end != c)
			(*end)++;
		if (**end)
			(*end)++;
	}
	else if (ft_strchr(CH_SPCL, c))
		while (**end && ft_strchr(CH_SPCL, **end))
			(*end)++;
	else
		while (**end && **end != ' ')
			(*end)++;
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
