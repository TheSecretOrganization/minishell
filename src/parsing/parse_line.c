/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:32:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Tokenize a line
 * @param tk pointer to the head of the list
 * @param line line to tokenize
 * @return t_code return C_SUCCES or C_ERR_MEM if malloc fails
*/
static t_code	init_tokens(t_token **tk, char *line)
{
	t_token	*tmp;

	tmp = NULL;
	while (*line)
	{
		tmp = t_token_new(line++);
		if (!tmp)
			return (t_token_clear(tk), \
			error(C_ERR_MEM, "t_token_new", ERR_MEM));
		t_token_addback(tk, tmp);
	}
	return (C_SUCCES);
}

/**
 * Assign the special char tokens their final values
 * @param tk head of the list
 * @return t_code return C_SUCCES or C_BAD_USAGE if there is unclosed quotes
*/
static t_code	init_spcl_chars(t_token *tk)
{
	size_t	nb[2];

	nb[0] = 0;
	nb[1] = 0;
	while (tk)
	{
		if (nb[0] % 2 && tk->val != CHAR && tk->val != QUOTE)
			tk->val = CHAR;
		if (nb[1] % 2 && tk->val != CHAR && tk->val != D_QUOTE && \
		tk->val != VARIABLE)
			tk->val = CHAR;
		if ((tk->val == QUOTE && ++(nb[0])) || \
		(tk->val == D_QUOTE && ++(nb[1])))
			;
		tk = tk->next;
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
	t_token	*tk;

	tk = NULL;
	if (init_tokens(&tk, *line))
		clean_exit(C_ERR_MEM, cmd, line, &tk);
	if (init_spcl_chars(tk))
		clean_exit(C_BAD_USE, cmd, line, &tk);
}
