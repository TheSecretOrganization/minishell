/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:45:11 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/27 13:47:48 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_code	error_front(char *line, size_t pos)
{
	size_t	i;
	size_t	nb;

	i = pos + 1;
	nb = 0;
	if (line[i] == line[pos])
		i++;
	while (line[i] && line[i] != line[pos])
		i++;
	if (!line[i])
		return (error_syntax(C_BAD_USE, NULL, 0));
	while (line[i + nb] == line[pos])
		nb++;
	if (nb == 1 && !(line[i] == '<' && line[i + nb] == '>'))
		return (error_syntax(C_BAD_USE, line + i, 1));
	return (error_syntax(C_BAD_USE, line + i, 2));
}

/**
 * @brief Check the syntax of in redirection char
 *
 * @param line line to check
 * @param pos position in line
 * @return t_code C_SUCCESS or an error
 */
t_code	check_in(char *line, size_t pos)
{
	size_t	nb;

	nb = 0;
	while (line[pos + nb] == '<')
		nb++;
	if (nb == 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 1));
	if (nb > 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 2));
	if (!check_for_alnum_chars(line, pos, line[pos], B_FALSE))
		return (error_front(line, pos));
	return (C_SUCCESS);
}

/**
 * @brief Check the syntax of out redirection char
 *
 * @param line line to check
 * @param pos position in line
 * @return t_code C_SUCCESS or an error
 */
t_code	check_out(char *line, size_t pos)
{
	size_t	nb;

	nb = 0;
	while (line[pos + nb] == '>')
		nb++;
	if (nb == 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 1));
	if (nb > 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 2));
	if (!check_for_alnum_chars(line, pos, line[pos], B_FALSE))
		return (error_front(line, pos));
	return (C_SUCCESS);
}
