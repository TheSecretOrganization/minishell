/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/24 11:03:38 by abasdere         ###   ########.fr       */
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
	if (!*cmd)
		return (free(*cmd), error(C_MEM, "ft_calloc", M_MEM));
	return (C_SUCCESS);
}

/**
 * Split the arguments of a command
 * @param target pointer on the targeted command
 * @param j_args pointer on the arguments to split
 * @return t_code C_SUCCESS or an error
*/
static t_code	split_args(t_cmd	**target, char **j_args)
{
	if (!target || !*target || !j_args || !*j_args)
		return (C_BAD_USE);
	(*target)->args = ft_split(*j_args, ' ');
	(free(*j_args), *j_args = NULL);
	if (!(*target)->args)
		return (error(C_MEM, "ft_split", M_MEM));
	return (C_SUCCESS);
}

/**
 * Add a new command to the AST
 * @param target pointer on the current target
 * @param line line parsed
 * @param i pointer on the index into line
 * @return t_code C_SUCCESS or an error
*/
static t_code	add_ope(t_cmd **target, char *line, size_t *i)
{
	t_cmd	*tmp;
	t_type	type;
	t_bool	same;

	tmp = NULL;
	type = T_PIPE;
	same = B_FALSE;
	if (line[*i] == line[*i + 1])
		same = B_TRUE;
	if (same && line[*i] == '&')
		type = T_PIPE_AND;
	else if (same && line[*i] == '|')
		type = T_PIPE_OR;
	if (o_init_cmd(&tmp))
		return (C_MEM);
	if (addback_cmd(*target, new_element(type, tmp)))
		return (free(tmp), error(C_MEM, "addback_cmd", M_MEM));
	*i += 1 + same;
	return (*target = tmp, C_SUCCESS);
}

/**
 * Join the new argument argument with the joined ones
 * @param j_args joined arguments
 * @param line line parsed
 * @param next new argument
 * @param i pointer on the position in the line
 * @return t_code C_SUCCES or an error
*/
static t_code	join_args(char	**j_args, char *line, char *next, size_t *i)
{
	if (!j_args || !line || !next || !i)
		return (C_BAD_USE);
	*j_args = fspace_njoin(*j_args, line + (*i), next - &(line[*i]));
	if (!*j_args)
		return (C_MEM);
	return (*i = next - &(line[0]), C_SUCCESS);
}

/**
 * Create the AST of commands
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or an error
*/
t_code	create_ast(t_data *data)
{
	char	*j_args;
	char	*next;
	t_cmd	*target;
	size_t	i;

	if (o_init_cmd(&(data->cmd)))
		(clean_memory(data, NULL), exit(C_MEM));
	j_args = NULL;
	i = 0;
	target = data->cmd;
	while (data->line[i] && data->line[i + 1])
	{
		next = find_next_sep(&(data->line[i + 1]));
		if (ft_strchr(CH_OPE, data->line[i]))
		{
			if (split_args(&target, &j_args)
				|| add_ope(&target, data->line, &i))
				(clean_memory(data, NULL), exit(C_MEM));
		}
		else if (join_args(&j_args, data->line, next, &i))
			(clean_memory(data, NULL), exit(C_MEM));
	}
	if (split_args(&target, &j_args) == C_MEM)
		(clean_memory(data, NULL), exit(C_MEM));
	return (C_SUCCESS);
}
