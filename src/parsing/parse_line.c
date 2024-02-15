/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 11:00:15 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check if the char is a space or a tab
 *
 * @param c char to check
 * @return int
 */
int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
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
	ft_putstr_fd("Syntax error near unexpected token `", STDERR_FILENO);
	if (el)
		while (*el && ++i < n)
			ft_putchar_fd(*(el++), STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	return (code);
}

/**
 * Parse user's input, exit the program if error occurs
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or an error code
*/
t_code	parse_line(t_data *data)
{
	t_code	code;

	code = check_syntax(data);
	if (code == C_BAD_USE)
		return (free(data->line), data->line = NULL, C_BAD_USE);
	else if (code == C_MEM)
		(ft_fsplit(data->envp), clean_data(data), exit(C_MEM));
	code = create_ast(data);
	if (code == C_BAD_USE)
		return (free(data->line), data->line = NULL, C_BAD_USE);
	else if (code == C_MEM)
		(ft_fsplit(data->envp), clean_data(data), exit(C_MEM));
	return (free(data->line), data->line = NULL, C_SUCCESS);
}
