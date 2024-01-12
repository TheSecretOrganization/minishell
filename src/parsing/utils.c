/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 17:30:34 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Free the allocated memory
 * @param code return code
 * @param cmd list of commands to free, nullable
 * @param line pointer on the line to free, nullable
 * @param tk list of tokens to free, nullable
 * @return t_code
*/
t_code	clean_memory(t_code code, t_cmd *cmd, char **line, t_token **tk)
{
	if (cmd)
		free_cmd(cmd);
	if (line && *line)
		free(*line);
	if (tk)
		t_token_clear(tk);
	return (code);
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
