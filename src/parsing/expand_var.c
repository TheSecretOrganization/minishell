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
 * @param data pointer on where the data is stored
 * @param i pointer on the position in the line
 * @return char * or NULL if an error occurs
 */
char	*expand_variable(t_data *data, size_t *i)
{
	size_t	len;
	char	*td;
	char	*tr;

	len = 1;
	while (ft_isalnum(data->line[*i + len]))
		len++;
	td = ft_substr(data->line, *i, len);
	if (!td)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	tr = ft_getenv(*data, td + 1);
	if (!tr)
	{
		data->line = ft_fstrrplc(data->line, td, "");
		(*i)--;
	}
	else
	{
		data->line = ft_fstrrplc(data->line, td, tr);
		free(tr);
	}
	if (!data->line)
		return (free(td), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(td), data->line);
}

/**
 * @brief Expand the path to the home of the current user
 *
 * @param data pointer on where the data is stored
 * @param i pointer on the position in the line
 * @return char * or NULL if an error occurs
 */
static char	*expand_home(t_data *data, size_t *i)
{
	char	*td;
	char	*tr;

	td = ft_substr(data->line, *i, 1);
	if (!td)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	tr = ft_getenv(*data, "HOME");
	if (!tr)
	{
		data->line = ft_fstrrplc(data->line, td, "");
		(*i)--;
	}
	else
	{
		data->line = ft_fstrrplc(data->line, td, tr);
		free(tr);
	}
	if (!data->line)
		return (free(td), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(td), data->line);
}

/**
 * @brief Expand the status code of the last command
 *
 * @param data pointer on where the data is stored
 * @return char * or NULL if an error occurs
 */
char	*expand_status(t_data *data)
{
	char	*tr;

	tr = ft_itoa(data->status);
	if (!tr)
		return (error(C_MEM, "ft_itoa", M_MEM), NULL);
	data->line = ft_fstrrplc(data->line, "$?", tr);
	if (!data->line)
		return (free (tr), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(tr), data->line);
}

/**
 * @brief Expand all variables in the line
 *
 * @param data pointer on where the data is stored
 * @param i pointer on the position in line
 * @param nd number of double quotes parsed
 * @return char * or NULL if an error occurs
 */
t_code	expand_var(t_data *data, size_t *i, size_t nd)
{
	if (data->line[*i] == '~' && !(nd % 2) && (ft_is_space(data->line[*i + 1])
			|| ft_strchr(CH_SPCL, data->line[*i + 1])))
	{
		if (!expand_home(data, i))
			return (C_MEM);
	}
	else if (data->line[*i] == '$' && data->line[*i + 1])
	{
		if (data->line[*i + 1] == '?')
			expand_status(data);
		else if (ft_isalnum(data->line[*i + 1]))
			expand_variable(data, i);
		if (!data->line)
			return (C_MEM);
	}
	return (C_SUCCESS);
}
