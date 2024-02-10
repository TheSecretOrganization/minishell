/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spcl_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:53:46 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/09 22:41:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check pipe syntax in line
 *
 * @param line line to check
 * @param pos position in line
 * @param forced_err call the error syntax on purpose
 * @return t_code C_SUCCESS or an error
 */
static t_code	check_pipe(char *line, size_t *pos, t_bool forced_err)
{
	size_t	nb;
	size_t	i;

	nb = 1;
	if (line[*pos + 1] == '&')
		return (error_syntax(C_BAD_USE, line + *pos, 2));
	if (line[*pos + 1] == '|')
		nb++;
	if (forced_err || !*pos)
		return (error_syntax(C_BAD_USE, line + *pos, nb));
	i = *pos - 1;
	while (i > 0 && !ft_strchr(CH_SPCL, line[i]) && line[i] == ' ')
		i--;
	if (!ft_strchr(CH_SPCL, line[i]) && line[i] != ' ')
		return (*pos += nb - 1, C_SUCCESS);
	return (error_syntax(C_BAD_USE, line + *pos, nb));
}

/**
 * @brief Check ampersand syntax in line
 *
 * @param line line to check
 * @param pos position in line
 * @return t_code C_SUCCESS or an error
 */
static t_code	check_ampersand(char *line, size_t *pos)
{
	size_t	nb;
	size_t	i;

	nb = 1;
	if (line[*pos + 1] == '&')
		nb++;
	if (!*pos || nb == 1)
		return (error_syntax(C_BAD_USE, line + *pos, nb));
	i = *pos - 1;
	while (i > 0 && !ft_strchr(CH_SPCL, line[i]) && line[i] == ' ')
		i--;
	if (!ft_strchr(CH_SPCL, line[i]) && line[i] != ' ')
	{
		if (line[*pos + nb] == '|')
			return (*pos += nb, check_pipe(line, pos, B_TRUE));
		return (*pos += nb - 1, C_SUCCESS);
	}
	return (error_syntax(C_BAD_USE, line + *pos, nb));
}

/**
 * @brief Check the syntax of in redirection char
 *
 * @param line line to check
 * @param pos position in line
 * @param forced_err call the error syntax on purpose
 * @return t_code C_SUCCESS or an error
 */
t_code	check_in(char *line, size_t *pos, t_bool force_err)
{
	size_t	nb;
	size_t	i;

	nb = 1;
	if (line[*pos + nb] == '<' || line[*pos + nb] == '>')
		nb++;
	if (force_err)
		return (error_syntax(C_BAD_USE, line + *pos, nb));
	i = *pos + nb;
	while (line[i] && !ft_strchr(CH_DIR, line[i]) && line[i] == ' ')
		i++;
	if (line[i] == '<')
		return (*pos = i, check_in(line, pos, B_TRUE));
	else if (line[i] == '>')
		return (*pos = i, check_out(line, pos, B_TRUE));
	else if (line[i] && line[i] != ' ')
		return (*pos += nb - 1, C_SUCCESS);
	return (error_syntax(C_BAD_USE, line + *pos, nb));
}

/**
 * @brief Check the syntax of out redirection char
 *
 * @param line line to check
 * @param pos position in line
 * @param forced_err call the error syntax on purpose
 * @return t_code C_SUCCESS or an error
 */
t_code	check_out(char *line, size_t *pos, t_bool force_err)
{
	size_t	nb;
	size_t	i;

	nb = 1;
	if (line[*pos + nb] == '>')
		nb++;
	if (force_err)
		return (error_syntax(C_BAD_USE, line + *pos, nb));
	i = *pos + nb;
	while (line[i] && !ft_strchr(CH_DIR, line[i]) && line[i] == ' ')
		i++;
	if (line[i] == '<')
		return (*pos = i, check_in(line, pos, B_TRUE));
	else if (line[i] == '>')
		return (*pos = i, check_out(line, pos, B_TRUE));
	else if (line[i] && line[i] != ' ')
		return (*pos += nb - 1, C_SUCCESS);
	return (error_syntax(C_BAD_USE, line + *pos, nb));
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
		if (line[i] == '&' && check_ampersand(line, &i))
			return (C_BAD_USE);
		if (line[i] == '|' && check_pipe(line, &i, B_FALSE))
			return (C_BAD_USE);
		if (line[i] == '<' && check_in(line, &i, B_FALSE))
			return (C_BAD_USE);
		if (line[i] == '>' && check_out(line, &i, B_FALSE))
			return (C_BAD_USE);
	}
	return (C_SUCCESS);
}
