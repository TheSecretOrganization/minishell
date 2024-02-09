/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/05 12:28:33 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Expand a variable if it is found in the env
 *
 * @param line line to parse
 * @param i pointer on the position in the line
 * @return char * or NULL if an error occurs
 */
char	*expand_variable(char *line, size_t *i)
{
	size_t	len;
	char	*td;
	char	*tr;

	len = 1;
	while (ft_isalnum(line[*i + len]))
		len++;
	td = ft_substr(line, *i, len);
	if (!td)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	tr = getenv(td + 1);
	if (!tr)
	{
		line = ft_fstrrplc(line, td, "");
		(*i)--;
	}
	else
		line = ft_fstrrplc(line, td, tr);
	if (!line)
		return (free(td), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(td), line);
}

/**
 * @brief Expand the path to the home of the current user
 *
 * @param line line to parse
 * @param i pointer on the position in the line
 * @return char * or NULL if an error occurs
 */
static char	*expand_home(char *line, size_t *i)
{
	char	*td;
	char	*tr;

	td = ft_substr(line, *i, 1);
	if (!td)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	tr = getenv("HOME");
	if (!tr)
	{
		line = ft_fstrrplc(line, td, "");
		(*i)--;
	}
	else
		line = ft_fstrrplc(line, td, tr);
	if (!line)
		return (free(td), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(td), line);
}

/**
 * @brief Expand the status code of the last command
 *
 * @param line line to parse
 * @param status status of the last command
 * @return char * or NULL if an error occurs
 */
char	*expand_status(char *line, int status)
{
	char	*tr;

	tr = ft_itoa(status);
	if (!tr)
		return (error(C_MEM, "ft_itoa", M_MEM), NULL);
	line = ft_fstrrplc(line, "$?", tr);
	if (!line)
		return (free (tr), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(tr), line);
}

/**
 * @brief Expand all variables in the line
 *
 * @param line pointer on the line to parse
 * @param i pointer on the position in line
 * @param status status code of the last command
 * @param nd number of double quotes parsed
 * @return char * or NULL if an error occurs
 */
t_code	expand_var(char **line, size_t *i, int status, size_t nd)
{
	if ((*line)[*i] == '~' && !(nd % 2)
		&& ((*line)[*i + 1] == ' ' || ft_strchr(CH_SPCL, (*line)[*i + 1])))
	{
		(*line) = expand_home((*line), i);
		if (!(*line))
			return (C_MEM);
	}
	else if ((*line)[*i] == '$' && (*line)[*i + 1] && (*line)[*i + 1] != ' ')
	{
		if ((*line)[*i + 1] == '?')
			(*line) = expand_status((*line), status);
		else
			(*line) = expand_variable((*line), i);
		if (!(*line))
			return (C_MEM);
	}
	return (C_SUCCESS);
}
