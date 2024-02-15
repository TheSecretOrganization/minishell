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
char	*expand_variable(t_data *data, size_t i, int add_q)
{
	size_t	len;
	char	*td;
	char	*tr;

	len = 1;
	while (ft_isalnum(data->line[i + len]))
		len++;
	td = ft_substr(data->line, i, len);
	if (!td)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	tr = ft_getenv(*data, td + 1);
	if (!tr)
		data->line = join_and_replace(data->line, td, "", add_q);
	else
	{
		data->line = join_and_replace(data->line, td, tr, add_q);
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
char	*expand_status(t_data *data, int add_q)
{
	char	*tr;

	tr = ft_itoa(data->status);
	if (!tr)
		return (error(C_MEM, "ft_itoa", M_MEM), NULL);
	data->line = join_and_replace(data->line, "$?", tr, add_q);
	if (!data->line)
		return (free (tr), error(C_MEM, "ft_fstrrplc", M_MEM), NULL);
	return (free(tr), data->line);
}

/**
 * @brief Expand all variables in the line
 *
 * @param data pointer on where the data is stored
 * @param i pointer on the position in line
 * @return char * or NULL if an error occurs
 */
t_code	expand_var(t_data *data, size_t i)
{
	if (data->line[i] == '$'
		&& (data->line[i + 1] == '?' || ft_isalpha(data->line[i + 1])))
	{
		if (data->line[i + 1] == '?')
			expand_status(data, 1);
		else if (ft_isalnum(data->line[i + 1]))
			expand_variable(data, i, 1);
		if (!data->line)
			return (C_MEM);
	}
	return (C_SUCCESS);
}
