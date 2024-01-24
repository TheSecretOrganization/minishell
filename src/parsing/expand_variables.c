/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/24 20:06:14 by abasdere         ###   ########.fr       */
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
static char	*expand_variable(char *line, size_t *i)
{
	size_t	len;
	char	*td;
	char	*tr;

	len = 1;
	// while (line[*i + len] && ft_isalnum(line[*i + len]))
	while (line[*i + len] && !ft_strchr(CH_SPCL, line[*i + len]))
		len++;
	td = ft_substr(line, *i, len);
	if (!td)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	tr = getenv(td + 1);
	if (!tr)
	{
		len = -1;
		line = ft_fstrrplc(line, td, "");
	}
	else
	{
		len = ft_strlen(tr) - 1;
		line = ft_fstrrplc(line, td, tr);
	}
	if (!line)
		return (free(td), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(td), *i += len, line);
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
	size_t	len;
	char	*td;
	char	*tr;

	td = ft_substr(line, *i, 1);
	if (!td)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	tr = getenv("HOME");
	if (!tr)
	{
		len = -1;
		line = ft_fstrrplc(line, td, "");
	}
	else
	{
		len = ft_strlen(tr) - 1;
		line = ft_fstrrplc(line, td, tr);
	}
	if (!line)
		return (free(td), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(td), *i += len, line);
}

/**
 * @brief Expand the status code of the last command
 *
 * @param line line to parse
 * @param i pointer on the position in the line
 * @return char * or NULL if an error occurs
 */
static char	*expand_status(char *line, int status, size_t *i)
{
	size_t	len;
	char	*tr;

	tr = ft_itoa(status);
	if (!tr)
		return (error(C_MEM, "ft_itoa", M_MEM), NULL);
	len = ft_strlen(tr) - 1;
	line = ft_fstrrplc(line, "$?", tr);
	if (!line)
		return (free (tr), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(tr), *i += len, line);
}

/**
 * @brief Expand all variables in the line
 *
 * @param line line to parse
 * @param status status code of the last command
 * @return char * or NULL if an error occurs
 */
char	*expand_variables(char *line, int status)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '~'
			&& (line[i + 1] == ' ' || ft_strchr(CH_SPCL, line[i + 1])))
		{
			line = expand_home(line, &i);
			if (!line)
				return (NULL);
		}
		else if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
		{
			if (line[i + 1] == '?')
				line = expand_status(line, status, &i);
			else
				line = expand_variable(line, &i);
			if (!line)
				return (NULL);
		}
	}
	return (line);
}
