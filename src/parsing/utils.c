/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/18 11:17:08 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Free the allocated memory
 * @param cmd list of commands to free, nullable
 * @param line line to free, nullable
 * @param args split line to free, nullable
*/
void	clean_memory(t_cmd *cmd, char *line, char **args)
{
	if (cmd)
		free_cmd(cmd);
	if (line)
		(free(line), line = NULL);
	if (args)
		(ft_fsplit(args), args = NULL);
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
	ft_putstr_fd(PROMPT_HEAD":", STDERR_FILENO);
	if (el)
	{
		ft_putstr_fd(" syntax error near unexpected token `", STDERR_FILENO);
		while (el && ++i < n)
			ft_putchar_fd(*(el++), STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (code);
}
