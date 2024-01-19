/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_abs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/19 15:49:34 by abasdere         ###   ########.fr       */
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

static t_code	split_args(t_cmd	**target, char **join_args)
{
	(*target)->args = ft_split(*join_args, ' ');
	(free(*join_args), *join_args = NULL);
	if (!(*target)->args)
		return (error(C_MEM, "ft_split", M_MEM));
	return (C_SUCCESS);
}

static t_code	add_ope(t_cmd **target, char *line, size_t *i)
{
	t_cmd	*tmp;
	t_bool	same;
	t_type	type;

	tmp = NULL;
	same = B_FALSE;
	if (line[*i] == line[*i + 1])
		same = B_TRUE;
	type = T_PIPE + same;
	if (same && line[*i] == '|')
		type++;
	if (o_init_cmd(&tmp))
		return (C_MEM);
	if (addback_cmd(*target, new_element(type, tmp)))
		return (free(tmp), error(C_MEM, "addback_cmd", M_MEM));
	*i += 1 + same;
	return (*target = tmp, C_SUCCESS);
}

static void	print_abs(t_cmd *cmd)
{
	size_t	i;
	size_t	nb;

	nb = 0;
	while (cmd)
	{
		i = -1;
		while (cmd->args[++i])
			printf("%ld: %s\n", nb, cmd->args[i]);
		nb++;
		if (cmd->elements[0] && cmd->elements[0]->value)
			cmd = cmd->elements[0]->value;
		else
			cmd = NULL;
	}
}

/**
 * Create the ABS
 * @param cmd pointer to the root of the ABS
 * @param line line to parse
 * @return t_code C_SUCCESS or an error
*/
t_code	create_abs(t_cmd **cmd, char *line)
{
	char	*j_args;
	char	*next;
	t_cmd	*target;
	size_t	i;

	if (o_init_cmd(cmd))
		(clean_memory(NULL, line, NULL), exit(C_MEM));
	j_args = NULL;
	i = 0;
	target = *cmd;
	while (line[i] && line[i + 1])
	{
		next = find_next_sep(&(line[i + 1]));
		if (ft_strchr(CH_OPE, line[i]))
		{
			if (split_args(&target, &j_args) || add_ope(&target, line, &i))
				(clean_memory(*cmd, line, NULL), exit(C_MEM));
		}
		else
		{
			j_args = fspace_njoin(j_args, line + i, next - &(line[i]));
			if (!j_args)
				(clean_memory(*cmd, &(line[0]), NULL), exit(C_MEM));
			i = next - &(line[0]);
		}
	}
	if (split_args(&target, &j_args))
		(clean_memory(*cmd, line, NULL), exit(C_MEM));
	print_abs(*cmd);
	return (C_SUCCESS);
}
