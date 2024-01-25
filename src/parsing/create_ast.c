/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/25 10:07:18 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Allocate a command
 * @param cmd pointer to the command to init
 * @return t_code C_SUCCESS or an error
*/
static t_code	o_init_cmd(t_cmd **cmd)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd)
		return (error(C_MEM, "ft_calloc", M_MEM));
	(*cmd)->args = NULL;
	(*cmd)->elements = ft_calloc(1, sizeof(t_element *));
	if (!(*cmd)->elements)
		return (free(*cmd), *cmd = NULL, error(C_MEM, "ft_calloc", M_MEM));
	return (C_SUCCESS);
}

/**
 * Add a new command to the AST
 * @param ast pointer on the control structure
 * @param line line parsed
 * @return t_code C_SUCCESS or an error
*/
static t_code	add_ope(t_ast *ast, char *line)
{
	t_cmd	*tmp;
	t_type	type;
	t_bool	same;

	tmp = NULL;
	type = T_PIPE;
	same = B_FALSE;
	if (split_args(&ast) == C_MEM)
		return (C_MEM);
	if (line[ast->i] == line[ast->i + 1])
		same = B_TRUE;
	if (same && line[ast->i] == '&')
		type = T_PIPE_AND;
	else if (same && line[ast->i] == '|')
		type = T_PIPE_OR;
	if (o_init_cmd(&tmp))
		return (C_MEM);
	if (addback_cmd(ast->target, new_element(type, tmp)))
		return (free(tmp), error(C_MEM, "addback_cmd", M_MEM));
	ast->i += 1 + same;
	return (ast->target = tmp, C_SUCCESS);
}

/**
 * @brief Add a new direction to the command
 *
 * @param ast pointer on the control structure
 * @param line line parsed
 * @return t_code C_SUCCESS or an error
 */
static t_code	add_dir(t_ast *ast, char *line)
{
	(void)ast;
	(void)line;
	return (C_SUCCESS);
}

/**
 * Create the AST of commands
 * @param data pointer on the data of the program
 * @return t_code C_SUCCESS or an error
*/
t_code	create_ast(t_data *data)
{
	t_ast	ast;

	if (o_init_cmd(&(data->cmd)))
		(clean_data(data), exit(C_MEM));
	ast.j_args = NULL;
	ast.i = 0;
	ast.target = data->cmd;
	while (data->line[ast.i] && data->line[ast.i + 1])
	{
		ast.next = find_next_sep(&(data->line[ast.i + 1]));
		ast.status = 0;
		if (ft_strchr(CH_OPE, data->line[ast.i]) && ++(ast.status)
			&& add_ope(&ast, data->line))
			return (C_MEM);
		if (ft_strchr(CH_DIR, data->line[ast.i]) && ++(ast.status)
			&& add_dir(&ast, data->line))
			return (free(ast.j_args), C_MEM);
		if (!ast.status && join_args(&ast, data->line))
			return (C_MEM);
	}
	if (split_args(&ast) == C_MEM)
		return (C_MEM);
	return (C_SUCCESS);
}
