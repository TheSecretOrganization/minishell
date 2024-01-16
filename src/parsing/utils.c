/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/16 16:56:18 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Free the allocated memory
 * @param cmd list of commands to free, nullable
 * @param line line to free, nullable
 * @param tk list of tokens to free, nullable
 * @param tks array of list of tokens to free, nullable
*/
void	clean_memory(t_cmd *cmd, char *line, t_token *tk, t_token **tks)
{
	size_t	i;

	i = -1;
	if (cmd)
		free_cmd(cmd);
	if (line)
		free(line);
	if (tk)
		free(tk);
	if (tks)
		free_tokens(tks);
}

/**
 * Write error statement to stderr
 * @param code exit code to return
 * @param el element which caused the error, nullable
 * @return t_code error code
*/
t_code	error_syntax(t_code code, char el)
{
	ft_putstr_fd(PROMPT_HEAD":", STDERR_FILENO);
	if (el)
		ft_dprintf(STDERR_FILENO, \
		" syntax error near unexpected token `%c'", el);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (code);
}

/**
 * Print a list of tokens
 * @param tk list to print
*/
void	print_tokens(t_token *tk)
{
	size_t	i;

	i = -1;
	while (tk[++i].id)
		printf("%d", tk[i].val);
	printf("\n");
}
