/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/18 22:41:58 by abasdere         ###   ########.fr       */
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
static void	init_cmd(t_cmd **cmd, char *line, char **args, t_cmd **target)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd)
		(free(line), exit(error(C_MEM, "ft_calloc", M_MEM)));
	(*cmd)->args = NULL;
	(*cmd)->elements = ft_calloc(1, sizeof(t_element *));
	if (!*cmd && !clean_memory(*cmd, line, NULL))
		exit(error(C_MEM, "ft_calloc", M_MEM));
	*args = NULL;
	*target = *cmd;
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

static char	*fspace_njoin(char *s1, char *s2, size_t n)
{
	size_t	len;
	size_t	i;
	char	*join;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	join = ft_calloc(len + n + 2, sizeof(char));
	if (!join)
		return (free(s1), NULL);
	i = -1;
	while (++i < len)
		join[i] = s1[i];
	join[len] = ' ';
	i = -1;
	while (++i < n)
		join[len + 1 + i] = s2[i];
	return (free(s1), join);
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

	(init_cmd(cmd, line, &args, &target), i = 0);
	while (line[i] && line[i + 1])
	{
		next = find_next_sep(&(line[i + 1]));
		if (ft_strchr(CH_OPE, line[i]))
		{
			target->args = ft_split(args, ' ');
			if (!target->args)
				(clean_memory(*cmd, line, args), exit(error(C_MEM, "ft_split", M_MEM)));
			(free(args), args = NULL);
		}
		// else if (ft_strchr(CH_DIR, *line))
		// {

		// }
		else
		{
			args = fspace_njoin(args, line + i, next - &(line[i]));
			if (!args)
				(clean_memory(*cmd, &(line[0]), NULL), exit(error(C_MEM, "fspace_njoin", M_MEM)));
		}
		i = next - &(line[0]);
	}
	clean_memory(*cmd, line, NULL);
	return (clean_memory(NULL, NULL, args));
}
