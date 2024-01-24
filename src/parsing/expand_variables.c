/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:10 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/24 15:48:40 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	expand_variable(t_data *data, size_t i)
{
	size_t	len;
	char	*td;
	char	*tr;

	len = 1;
	while (data->line[i + len] && ft_isalnum(data->line[i + len]))
		len++;
	td = ft_substr(data->line, i, len);
	if (!td)
		(clean_memory(data, NULL), exit(error(C_MEM, "ft_substr", M_MEM)));
	tr = getenv(td + 1);
	if (!tr)
	{
		len = -1;
		data->line = ft_fstrrplc(data->line, td, "");
	}
	else
	{
		len = ft_strlen(tr) - 1;
		data->line = ft_fstrrplc(data->line, td, tr);
	}
	if (!data->line)
		(clean_memory(data, td), exit(error(C_MEM, "ft_fstrrplc", M_MEM)));
	return (free(td), i + len);
}

static size_t	expand_home(t_data *data, size_t i)
{
	size_t	len;
	char	*td;
	char	*tr;

	td = ft_substr(data->line, i, 1);
	if (!td)
		(clean_memory(data, NULL), exit(error(C_MEM, "ft_substr", M_MEM)));
	tr = getenv("HOME");
	if (!tr)
	{
		len = -1;
		data->line = ft_fstrrplc(data->line, td, "");
	}
	else
	{
		len = ft_strlen(tr) - 1;
		data->line = ft_fstrrplc(data->line, td, tr);
	}
	if (!data->line)
		(clean_memory(data, td), exit(error(C_MEM, "ft_fstrrplc", M_MEM)));
	return (free(td), i + len);
}

static size_t	expand_status(t_data *data, size_t i)
{
	size_t	len;
	char	*tr;

	tr = ft_itoa(data->status);
	if (!tr)
		(clean_memory(data, NULL), exit(error(C_MEM, "ft_itoa", M_MEM)));
	len = ft_strlen(tr) - 1;
	data->line = ft_fstrrplc(data->line, "$?", tr);
	if (!data->line)
		(clean_memory(data, tr), exit(error(C_MEM, "ft_fstrrplc", M_MEM)));
	return (free(tr), i + len);
}

size_t	expand_variables(t_data *data, size_t i)
{
	if (data->line[i] == '~' && (data->line[i + 1] == ' '
		|| ft_strchr(CH_SPCL, data->line[i + 1])))
		i = expand_home(data, i);
	else if (data->line[i] == '$')
	{
		if (data->line[i + 1] == '?')
			i = expand_status(data, i);
		else
			i = expand_variable(data, i);
	}
	return (i);
}
