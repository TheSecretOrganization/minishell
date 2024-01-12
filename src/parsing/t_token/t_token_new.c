/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:49:27 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:47:20 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Find the token value of a char
 * @param c char to tokenized
 * @return t_val
*/
static t_val	get_val(char c)
{
	if (ft_strchr("~`#()\\[]{};?!", c))
		return (V_ERROR);
	if (ft_strchr("&|<>", c))
		return (V_SPCL_CHAR);
	else if (c == '\"')
		return (V_DQUOTE);
	else if (c == '\'')
		return (V_QUOTE);
	else if (c == '$')
		return (V_VARIABLE);
	else if (c == '*')
		return (V_WILDCARD);
	else if (c == ' ')
		return (V_SEP);
	return (V_CHAR);
}

/**
 * Create a new t_token node
 * @param id value to tokenized
 * @return t_token	* or NULL if an error was encountered
*/
t_token	*t_token_new(char *id)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->val = get_val(*id);
	new->id = id;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
