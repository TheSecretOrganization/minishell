/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:16:58 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Tokenize a line
 * @param lst pointer to the head of the list
 * @param line line to tokenize
 * @return t_code return C_SUCCES or C_ERR_MEM if malloc fails
*/
static t_code	init_tokens(t_token **lst, char *line)
{
	t_token	*tmp;

	tmp = NULL;
	while (*line)
	{
		tmp = t_token_new(line++);
		if (!tmp)
			return (t_token_clear(lst), \
			error(C_ERR_MEM, "t_token_new", ERR_MEM));
		t_token_addback(lst, tmp);
	}
	return (C_SUCCES);
}

/**
 * Assign the special char tokens their final values
 * @param lst head of the list
 * @return t_code return C_SUCCES or C_BAD_USAGE if there is unclosed quotes
*/
static t_code	init_spcl_chars(t_token *lst)
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
	if (nb[0] % 2)
		return (error(C_BAD_USE, NULL, ERR_SYN"`''"));
	else if (nb[1] % 2)
		return (error(C_BAD_USE, NULL, ERR_SYN"`\"'"));
	return (C_SUCCES);
}

/**
 * Parse user's input, exit the program if error occurs
*/
void	parse_line(t_cmd *cmd, char **line)
{
	t_token	*lst;

	lst = NULL;
	if (init_tokens(&lst, *line))
		clean_exit(C_ERR_MEM, cmd, line, &lst);
	if (init_spcl_chars(lst))
		clean_exit(C_BAD_USE, cmd, line, &lst);
}
