/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:05:37 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/17 11:27:40 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Find the number of elements in the command and check their syntax
 * @param tk tokens to parse
 * @return size_t number of elements or 0 if an error occurs
*/
static size_t	find_nb_elements(t_token *tk)
{
	size_t	nb;

	nb = 0;
	while (tk && tk->val == V_SEP)
		tk++;
	while (tk)
	{
		nb++;

		while (tk && tk->val == V_SEP)
			tk++;
	}
	return (nb);
}

/**
 * Create a command ABS
 * @param cmd commands to init
 * @param tks tokens to compute
 * @return t_code C_SUCCESS or an error
*/
t_code	create_cmds(t_cmd **cmd, t_token **tks, char *line)
{
	size_t	i;

	i = -1;
	*cmd = ft_calloc(2, sizeof(t_cmd));
	if (!*cmd)
		return (C_MEM);
	while (tks[++i])
	{
		print_tokens(tks[i]);
	}
	return (C_SUCCESS);
}
