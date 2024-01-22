/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:54:29 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/22 09:46:00 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Check bash syntax in one line
 * @param line line to check
 * @return t_code C_SUCCESS or C_BAD_USE
*/
t_code	check_syntax(char *line)
{
	size_t	nq;
	size_t	nd;

	nq = 0;
	nd = 0;
	while (line && *line)
	{
		if (*line == '\'' && !(nd % 2))
			nq++;
		if (*line == '\"' && !(nq % 2))
			nd++;
		if (!(nq % 2) && !(nd % 2) && ft_strchr(CH_ERR, *line))
			return (error_syntax(C_BAD_USE, line, 1));
		line++;
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}
