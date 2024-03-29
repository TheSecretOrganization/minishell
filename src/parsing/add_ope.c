/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ope.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:18:54 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 08:49:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Allocate a command
 * @param cmd pointer to the command to init
 * @return t_code C_SUCCESS or an error
*/
t_code	o_init_cmd(t_cmd **cmd)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd)
		return (error(C_MEM, "ft_calloc", M_MEM));
	(*cmd)->args = ft_calloc(1, sizeof(char *));
	if (!(*cmd)->args)
		return (free(*cmd), *cmd = NULL, error(C_MEM, "ft_calloc", M_MEM));
	(*cmd)->elements = ft_calloc(1, sizeof(t_element *));
	if (!(*cmd)->elements)
		return (free((*cmd)->args), free(*cmd),
			*cmd = NULL, error(C_MEM, "ft_calloc", M_MEM));
	return (C_SUCCESS);
}

/**
 * Add a new command to the AST
 * @param ast pointer on the control structure
 * @return t_code C_SUCCESS or an error
*/
t_code	add_ope(t_ast *ast)
{
	t_cmd	*tmp;
	t_type	type;

	tmp = NULL;
	type = T_PIPE;
	if (ast->args[ast->i][0] == ast->args[ast->i][1]
		&& ast->args[ast->i][1] == '&')
		type = T_PIPE_AND;
	else if (ast->args[ast->i][0] == ast->args[ast->i][1]
		&& ast->args[ast->i][1] == '|')
		type = T_PIPE_OR;
	if (o_init_cmd(&tmp))
		return (free_args(ast), C_MEM);
	if (addback_cmd(ast->target, new_element(type, tmp)))
		return (free_args(ast), free(tmp), error(C_MEM, "addback_cmd", M_MEM));
	return (free(ast->args[ast->i]), ast->target = tmp, C_SUCCESS);
}
