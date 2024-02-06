/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:04 by averin            #+#    #+#             */
/*   Updated: 2024/02/06 13:32:41 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cmd_unset(t_exec *exec)
{
	size_t	i;
	char	*el;

	i = 0;
	if (exec->is_pipe || exec->args[0] == NULL || exec->args[1] == NULL)
		return (C_SUCCESS);
	while (exec->args[++i])
	{
		el = ft_getenv(*(exec->data), exec->args[i]);
		if (el)
			return (free(el), ft_unenv(exec->data, exec->args[i]));
		free(el);
	}
	return (C_SUCCESS);
}
