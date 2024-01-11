/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/11 19:55:05 by abasdere         ###   ########.fr       */
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

 * Assign the special char tokens their final values
 * @param lst head of the list
 * @return t_bool return B_TRUE or B_FALSE if there is unclosed (double) quotes
*/
static t_bool	init_spcl_chars(t_token *lst)
{
	size_t	nb[2];

	nb[0] = 0;
	nb[1] = 0;
	while (lst)
	{
		if (nb[0] % 2 && lst->val != CHAR && lst->val != QUOTE)
			lst->val = CHAR;
		if (nb[1] % 2 && lst->val != CHAR && lst->val != D_QUOTE && \
		lst->val != VARIABLE)
			lst->val = CHAR;
		if ((lst->val == QUOTE && ++(nb[0])) || \
		(lst->val == D_QUOTE && ++(nb[1])))
			;
		lst = lst->next;
	}
	if (nb[0] % 2 || nb[1] % 2)
		return (B_FALSE);
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
	if (!init_tokens(&lst, line) || !init_spcl_chars(lst))
		return (t_token_clear(&lst), B_FALSE);
	return (t_token_clear(&lst), B_TRUE);
}
