/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 10:38:41 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Join the new argument argument with the joined ones
 * @param ast pointer on the control structure
 * @return t_code C_SUCCES or an error
*/
static t_code	add_arg(t_ast *ast)
{
	char	**new;
	size_t	len;

	len = 0;
	while (ast->target->args[len])
		len++;
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (free_args(ast), C_MEM);
	len = -1;
	while (ast->target->args[++len])
		new[len] = ast->target->args[len];
	new[len] = ast->args[ast->i];
	(free(ast->target->args), ast->target->args = new);
	return (C_SUCCESS);
}

/**
 * @brief Create a new element according to it's type
 *
 * @param ast data of the ast
 * @return t_code C_SUCCESS or an error
 */
static t_code	create_element(t_ast *ast)
{
	if (ast->args[ast->i][0] != '\0' && ft_strchr(CH_OPE, ast->args[ast->i][0]))
	{
		if (!ast->target->args[0])
			(free(ast->target->args), ast->target->args = NULL);
		return (add_ope(ast));
	}
	else if (ast->args[ast->i][0] != '\0'
		&& ft_strchr(CH_DIR, ast->args[ast->i][0]))
		return (add_dir(ast));
	return (add_arg(ast));
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
		return (C_MEM);
	ast.args = split_line(data->line);
	if (!ast.args)
		return (C_MEM);
	ast.i = -1;
	ast.status = data->status;
	ast.envp = data->envp;
	ast.target = data->cmd;
	while (ast.args[++ast.i])
		if (create_element(&ast))
			return (C_MEM);
	free(ast.args);
	if (!ast.target->args[0])
		(free(ast.target->args), ast.target->args = NULL);
	return (C_SUCCESS);
}
