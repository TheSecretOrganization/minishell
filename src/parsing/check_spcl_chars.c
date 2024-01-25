/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spcl_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:53:46 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/25 17:42:18 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Print an error syntax for the extra pipe after the ampersand
 *
 * @param line line to check
 * @return t_code C_BAD_USAGE
 */
static t_code	error_pipe(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == '|' || line[i] == '&')
		i++;
	if (i == 1)
		return (error_syntax(C_BAD_USE, line, 1));
	return (error_syntax(C_BAD_USE, line, 2));
}

/**
 * @brief Check ampersand syntax in line
 *
 * @param line line to check
 * @param pos position in line
 * @return t_code C_SUCCESS or an error
 */
t_code	check_ampersand(char *line, size_t pos)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = pos;
	while (line[pos + nb] == '&')
		nb++;
	if (nb == 3)
		return (error_syntax(C_BAD_USE, line + pos, 1));
	if (nb > 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 2));
	if (pos && i--)
		while (i > 0 && line[i] != '&' && !ft_isalnum(line[i]))
			i--;
	if (!i && !ft_isalnum(line[i]))
		return (error_syntax(C_BAD_USE, line + pos, nb));
	i = pos + 1;
	while (line[i] && !ft_strchr(CH_OPE, line[i]) && !ft_isalnum(line[i]))
		i++;
	if (!line[i] || (line[pos - 1] != '&' && line[pos + 1] != '&'))
		return (error_syntax(C_BAD_USE, line + pos, nb));
	if (line[i] == '|')
		return (error_pipe(line + i));
	return (C_SUCCESS);
}

/**
 * @brief Check pipe syntax in line
 *
 * @param line line to check
 * @param pos position in line
 * @return t_code C_SUCCESS or an error
 */
t_code	check_pipe(char *line, size_t pos)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = pos;
	if (line[pos + 1] == '&')
		return (error_syntax(C_BAD_USE, line + pos, 2));
	while (line[pos + nb] == '|' || line[pos + nb] == '&')
		nb++;
	if (nb == 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 1));
	if (nb > 3)
		return (error_syntax(C_BAD_USE, line + pos + 2, 2));
	if (pos && i--)
		while (i > 0 && line[i] != '|' && !ft_isalnum(line[i]))
			i--;
	if (!i && (!ft_isalnum(line[i] || line[i])))
		return (error_syntax(C_BAD_USE, line + pos, nb));
	i = pos + 1;
	while (line[i] && line[i] != '|' && !ft_isalnum(line[i]))
		i++;
	if (!line[i])
		return (error_syntax(C_BAD_USE, line + pos, nb));
	return (C_SUCCESS);
}

/**
 * @brief Check special chars syntax in line
 *
 * @param line line to check
 * @return t_code C_SUCCESS or an error
 */
t_code	check_spcl_chars(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && check_pipe(line, i))
			return (C_BAD_USE);
		if (line[i] == '&' && check_ampersand(line, i))
			return (C_BAD_USE);
	}
	return (C_SUCCESS);
}
