/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:18:39 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/25 13:02:56 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Get the next substr object
 *
 * @param ast pointer on the top of the ast
 * @param line line parsed
 * @return char* or NULL
 */
static char	*get_next_substr(t_ast *ast, char *line)
{
	char	*sub;
	char	*new_next;

	new_next = find_next_sep(ast->next + 1);
	while (new_next - ast->next == 1)
	{
		ast->next = new_next;
		new_next = find_next_sep(ast->next + 1);
	}
	sub = ft_substr(line, (ast->next + 1) - \
	&(line[0]), new_next - (ast->next + 1));
	if (!sub)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	return (ast->next = new_next, sub);
}

/**
 * @brief Add a new infile element
 *
 * @param ast pointer on the control structure
 * @param line line parsed
 * @param type type of the infile
 * @return t_code C_SUCCESS or an error
 */
static t_code	add_in(t_ast *ast, char *line, t_intype type)
{
	t_infile	*file;

	file = ft_calloc(1, sizeof(t_infile));
	if (!file)
		return (error(C_MEM, "ft_calloc", M_MEM));
	file->intype = type;
	file->filename = get_next_substr(ast, line);
	if (!file->filename)
		return (free(file), C_MEM);
	if (addback_cmd(ast->target, new_element(T_INFILE, file)))
		return (free(file->filename), free(file), \
		error(C_MEM, "addback_cmd", M_MEM));
	return (ast->i = ast->next - &(line[0]), C_SUCCESS);
}

/**
 * @brief Add a new outfile element
 *
 * @param ast pointer on the control structure
 * @param line line parsed
 * @param type type of the outfile
 * @return t_code C_SUCCESS or an error
 */
static t_code	add_out(t_ast *ast, char *line, t_outtype type)
{
	t_outfile	*file;

	file = ft_calloc(1, sizeof(t_outfile));
	if (!file)
		return (error(C_MEM, "ft_calloc", M_MEM));
	file->outtype = type;
	file->filename = get_next_substr(ast, line);
	if (!file->filename)
		return (free(file), C_MEM);
	if (addback_cmd(ast->target, new_element(T_OUTFILE, file)))
		return (free(file->filename), free(file), \
		error(C_MEM, "addback_cmd", M_MEM));
	return (ast->i = ast->next - &(line[0]), C_SUCCESS);
}

/**
 * @brief Add a new direction element
 *
 * @param ast pointer on the control structure
 * @param line line parsed
 * @return t_code C_SUCCESS or an error
 */
t_code	add_dir(t_ast *ast, char *line)
{
	if (line[ast->i] == '<')
	{
		if (line[ast->i + 1] == '<')
			return (add_in(ast, line, IT_HERE_DOC));
		else
			return (add_in(ast, line, IT_INFILE));
	}
	else
	{
		if (line[ast->i + 1] == '>')
			return (add_out(ast, line, OT_APPEND));
		else
			return (add_out(ast, line, OT_TRUNCATE));
	}
	return (C_SUCCESS);
}