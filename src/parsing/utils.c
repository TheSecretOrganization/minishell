/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/22 09:47:20 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Free the allocated memory
 * @param cmd list of commands to free, nullable
 * @param line line to free, nullable
 * @param join_args struct to free, nullable
 * @return t_code C_SUCCESS
*/
t_code	clean_memory(t_cmd *cmd, char *line, char *join_args)
{
	if (cmd)
		free_cmd(cmd);
	if (line)
		free(line);
	if (join_args)
		free(join_args);
	return (C_SUCCESS);
}

/**
 * Write error statement to stderr
 * @param code exit code to return
 * @param el element which caused the error, nullable
 * @param n number of char from el to print
 * @return t_code error code
*/
t_code	error_syntax(t_code code, char *el, size_t n)
{
	size_t	i;

	i = -1;
	ft_putstr_fd(PROMPT_HEAD": syntax error near unexpected token `", \
	STDERR_FILENO);
	if (el)
		while (*el && ++i < n)
			ft_putchar_fd(*(el++), STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	return (code);
}

/**
 * Print a ATS of commands
 * @param cmd ats of commands to print
*/
void	print_ats(t_cmd *cmd)
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
 * Catenate a space and n char from one string to another
 * @param s1 destination string, will be free
 * @param s2 source string
 * @param n number of char to catenate
 * @return char * or NULL if an error occurs
*/
char	*fspace_njoin(char *s1, char *s2, size_t n)
{
	size_t	len;
	size_t	i;
	char	*join;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	join = ft_calloc(len + n + 2, sizeof(char));
	if (!join)
		return (free(s1), error(C_MEM, "ft_calloc", M_MEM), NULL);
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
 * Find the next separator in a line
 * @param line line to check
 * @return char * to the next seprator
*/
char	*find_next_sep(char *line)
{
	while (line && *line)
	{
		if (ft_strchr(CH_DIR, *line) || ft_strchr(CH_OPE, *line)
			|| *line == ' ')
			return (line);
		line++;
	}
	return (line);
}
