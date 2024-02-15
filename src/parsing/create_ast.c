/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 09:10:04 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Remove outer quotes from a line
 *
 * @param s pointer on the string to trim
 * @param d of the program, nullable
 * @param expand boolean to expand or not
 * @param remove boolean to remove or not
 */
int	remove_and_expand(char **s, t_data *d, int expand, int remove)
{
	size_t	nq;
	size_t	nd;
	size_t	i;

	nd = 0;
	nq = 0;
	i = -1;
	while ((*s)[++i])
	{
		if (expand && !(nq % 2) && ((d->line[i] == '$' && d->line[i + 1])
				|| (d->line[i] == '~' && !(nd % 2)
					&& ft_is_space(d->line[i + 1]))))
		{
			if (expand_var(d, i, nd))
				return (C_MEM);
			i--;
			continue ;
		}
		if (remove && (*s)[i] == '\'' && !(nd % 2) && ++nq)
			(ft_memcpy(&((*s)[i]), &((*s)[i + 1]), ft_strlen((*s)) - i), i--);
		else if (remove && (*s)[i] == '\"' && !(nq % 2) && ++nd)
			(ft_memcpy(&((*s)[i]), &((*s)[i + 1]), ft_strlen((*s)) - i), i--);
	}
	return (C_SUCCESS);
}

/**
 * Join the new argument argument with the joined ones
 * @param ast pointer on the control structure
 * @return t_code C_SUCCES or an error
*/
static t_code	add_arg(t_ast *ast)
{
	char	**new;
	size_t	len;
	t_data	cpy;

	cpy.status = ast->status;
	cpy.envp = ast->envp;
	cpy.line = ast->args[ast->i];
	if (remove_and_expand(&(cpy.line), &cpy, 1, 1))
		return (++(ast->i), free_args(ast), C_MEM);
	ast->args[ast->i] = cpy.line;
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
