/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:18:39 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 09:02:21 by abasdere         ###   ########.fr       */
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
static t_code	add_in(t_ast *ast, t_intype type)
{
	t_infile	*file;
	t_data		cpy;

	cpy.status = ast->status;
	cpy.envp = ast->envp;
	free(ast->args[ast->i++]);
	file = ft_calloc(1, sizeof(t_infile));
	if (!file)
		return (free_args(ast), error(C_MEM, "ft_calloc", M_MEM));
	file->intype = type;
	file->filename = ast->args[(ast->i)++];
	cpy.line = file->filename;
	if (type != IT_HERE_DOC)
		remove_and_expand(&(cpy.line), &cpy, 1, 0);
	else
		remove_and_expand(&(cpy.line), &cpy, 1, 1);
	if (!cpy.line)
		return (free(file), free_args(ast), C_MEM);
	file->filename = cpy.line;
	if (addback_cmd(ast->target, new_element(T_INFILE, file)))
		return (free_args(ast), free(file->filename),
			free(file), error(C_MEM, "addback_cmd", M_MEM));
	return (C_SUCCESS);
}

/**
 * @brief Add a new outfile element
 *
 * @param ast pointer on the control structure
 * @param type type of the outfile
 * @return t_code C_SUCCESS or an error
 */
static t_code	add_out(t_ast *ast, t_outtype type)
{
	t_outfile	*file;
	t_data		cpy;

	cpy.status = ast->status;
	cpy.envp = ast->envp;
	free(ast->args[ast->i++]);
	file = ft_calloc(1, sizeof(t_infile));
	if (!file)
		return (free_args(ast), error(C_MEM, "ft_calloc", M_MEM));
	file->outtype = type;
	file->filename = ast->args[(ast->i)++];
	cpy.line = file->filename;
	remove_and_expand(&(cpy.line), &cpy, 1, 1);
	if (!cpy.line)
		return (free(file), free_args(ast), C_MEM);
	file->filename = cpy.line;
	if (addback_cmd(ast->target, new_element(T_INFILE, file)))
		return (free_args(ast), free(file->filename),
			free(file), error(C_MEM, "addback_cmd", M_MEM));
	return (C_SUCCESS);
}

/**
 * @brief Add a new direction element
 *
 * @param ast pointer on the control structure
 * @return t_code C_SUCCESS or an error
 */
t_code	add_dir(t_ast *ast)
{
	if (ast->args[ast->i][0] == '<')
	{
		if (ast->args[ast->i][1] == '<')
			return (add_in(ast, IT_HERE_DOC));
		else if (ast->args[ast->i][1] == '>')
			return (add_in(ast, IT_CREATE));
		else
			return (add_in(ast, IT_INFILE));
	}
	else
	{
		if (ast->args[ast->i][1] == '>')
			return (add_out(ast, OT_APPEND));
		else
			return (add_out(ast, OT_TRUNCATE));
	}
}
