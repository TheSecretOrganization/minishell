/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/13 08:53:33 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Create a new element according to it's type
 *
 * @param data pointer on the data of the program
 * @param ast data of the ast
 * @return t_code C_SUCCESS or an error
 */
static t_code	create_element(t_data *data, t_ast *ast)
{
	ast->next = get_next_substr(ast, data->line);
	if (!ast->next)
		return (C_MEM);
	if (ast->next[0] != '\0' && ft_strchr(CH_OPE, ast->next[0]))
	{
		if (!ast->target->args[0])
			(free(ast->target->args), ast->target->args = NULL);
		return (add_ope(ast, data->line));
	}
	else if (ast->next[0] != '\0' && ft_strchr(CH_DIR, ast->next[0]))
		return (add_dir(ast, data->line));
	return (add_arg(ast, data->line));
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
	ast.i = 0;
	ast.target = data->cmd;
	while (data->line[ast.i])
		if (create_element(data, &ast))
			return (C_MEM);
	if (!ast.target->args[0])
		(free(ast.target->args), ast.target->args = NULL);
	return (C_SUCCESS);
}
