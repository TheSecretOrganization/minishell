/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/25 11:19:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
