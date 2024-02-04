/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:12 by averin            #+#    #+#             */
/*   Updated: 2024/02/03 21:45:57 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	process_arg(char *arg, t_data *data)
{
	char	*value;
	int		code;

	if (remove_quotes(&arg))
		return (C_MEM);
	value = ft_strchr(arg, '=');
	if (value)
		*(value++) = '\0';
	code = ft_setenv(data, arg, value);
	if (value)
		*(--value) = '=';
	return (code);
}

int	cmd_export(t_exec *exec)
{
	size_t	i;

	if (exec->args[0] == NULL)
		return (C_SUCCESS);
	else if (exec->args[1] == NULL)
		return (print_export(exec->data->envp));
	i = 0;
	while (exec->args[++i])
		if (process_arg(exec->args[i], exec->data))
			return (C_MEM);
	return (C_SUCCESS);
}
