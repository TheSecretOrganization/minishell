/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:18:39 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/10 12:03:36 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

	(free(ast->next), ast->i = ast->new_i - line);
	file = ft_calloc(1, sizeof(t_infile));
	if (!file)
		return (error(C_MEM, "ft_calloc", M_MEM));
	file->intype = type;
	file->filename = get_next_substr(ast, line);
	if (!file->filename)
		return (free(file), C_MEM);
	if (type != IT_HERE_DOC)
		remove_quotes(&file->filename);
	if (addback_cmd(ast->target, new_element(T_INFILE, file)))
		return (free(file->filename), free(file), \
		error(C_MEM, "addback_cmd", M_MEM));
	return (ast->i = ast->new_i - line, C_SUCCESS);
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

	(free(ast->next), ast->i = ast->new_i - line);
	file = ft_calloc(1, sizeof(t_outfile));
	if (!file)
		return (error(C_MEM, "ft_calloc", M_MEM));
	file->outtype = type;
	file->filename = get_next_substr(ast, line);
	if (!file->filename)
		return (free(file), C_MEM);
	remove_quotes(&(file->filename));
	if (addback_cmd(ast->target, new_element(T_OUTFILE, file)))
		return (free(file->filename), free(file), \
		error(C_MEM, "addback_cmd", M_MEM));
	return (ast->i = ast->new_i - line, C_SUCCESS);
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
	if (ast->next[0] == '<')
	{
		if (ast->next[1] == '<')
			return (add_in(ast, line, IT_HERE_DOC));
		else if (ast->next[1] == '>')
			return (add_in(ast, line, IT_CREATE));
		else
			return (add_in(ast, line, IT_INFILE));
	}
	else
	{
		if (ast->next[1] == '>')
			return (add_out(ast, line, OT_APPEND));
		else
			return (add_out(ast, line, OT_TRUNCATE));
	}
	return (C_SUCCESS);
}
