/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/11 19:34:05 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Tokenize a line
 * @param lst pointer to the head of the list
 * @param line line to tokenize
 * @return t_bool return B_TRUE or B_FALSE if malloc fails
*/
static t_bool	init_tokens(t_token **lst, char *line)
{
	t_token	*tmp;

	tmp = NULL;
	while (*line)
	{
		tmp = t_token_new(line++);
		if (!tmp)
			return (t_token_clear(lst), B_FALSE);
		t_token_addback(lst, tmp);
	}
	return (B_TRUE);
}

/**
 * Parse user's input
 * @return B_TRUE if user's input is valid, B_FALSE if it isn't
*/
t_bool	parse_line(t_cmd *cmd, char *line)
{
	t_token	*lst;

	lst = NULL;
	if (!init_tokens(&lst, line))
		return (B_FALSE);
	return (t_token_clear(&lst), B_TRUE);
}
