/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/18 17:33:35 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Init variables
 * @param cmd
 * @param line
 * @param args
 * @param target
*/
static void	init_cmd(t_cmd **cmd, char *line, char *args, t_cmd *target)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd)
		(free(line), exit(error(C_MEM, "ft_calloc", M_MEM)));
	(*cmd)->args = NULL;
	(*cmd)->elements = ft_calloc(1, sizeof(t_element *));
	if (!*cmd && !clean_memory(*cmd, line, NULL))
		exit(error(C_MEM, "ft_calloc", M_MEM));
	*args = NULL;
	target = *cmd;
}

static char	*find_next_sep(char *line)
{
	while (line && *line)
	{
		if (ft_strchr(CH_DIR, *line) || ft_strchr(CH_OPE, *line) \
		|| *line == ' ')
			return (line);
		line++;
	}
	return (line);
}

/**
 * Create the command ABS
 * @param cmd pointer to the root of the ABS
 * @param line line to parse
 * @return t_code C_SUCCESS or an error
*/
t_code	create_cmd(t_cmd **cmd, char *line)
{
	char	*args;
	char	*next;
	t_cmd	*target;
	size_t	i;

	(inits(cmd, line, &args, target), i = -1);
	while (line[++i])
	{
		next = find_next_sep(line);

	}
	clean_memory(*cmd, line, args);
	return (clean_memory(NULL, NULL, args));
}
