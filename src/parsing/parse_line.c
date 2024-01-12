/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 19:39:07 by abasdere         ###   ########.fr       */
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
		if (!(nb[0] % 2) && !(nb[1] % 2) && tk->val == V_ERROR)
			return (error_syntax(C_BAD_USE, *(tk->id)));
		if (nb[0] % 2 && tk->val != V_CHAR && tk->val != V_QUOTE)
			tk->val = V_CHAR;
		if (nb[1] % 2 && tk->val != V_CHAR && tk->val != V_DQUOTE && \
		tk->val != V_VARIABLE)
			tk->val = V_CHAR;
		if ((tk->val == V_QUOTE && ++(nb[0])) || \
		(tk->val == V_DQUOTE && ++(nb[1])))
			;
		if (tk->val == V_VARIABLE && tk->next && tk->next->val == V_CHAR)
			tk->next->val = V_VARIABLE;
		tk = tk->next;
	}
	if (nb[0] % 2)
		return (error_syntax(C_BAD_USE, '\''));
	else if (nb[1] % 2)
		return (error_syntax(C_BAD_USE, '\"'));
	return (C_SUCCES);
}

/**
 * Parse in function of their precedence
 * @param code return code
 * @param list of comamnd to init
 * @param tk head of the token list to parse
 * @param prec determine what level of tokens is being treated
 * @return t_token new position in the token list or NULL if a error occurs
*/
t_token	*parse_tokens(t_code *code, t_cmd **cmd, t_token *tk, t_val prec)
{
	if (prec == V_SEP)
		while (tk && tk->val == V_SEP)
			tk = tk->next;
	else if (prec == V_CHAR)
		;
	else if (prec == V_WILDCARD)
		return (error_syntax(C_BAD_USE, '*'), NULL);
	else if (prec == V_VARIABLE)
		;
	else if (prec == V_QUOTE)
		;
	else if (prec == V_DQUOTE)
		;
	else if (prec == V_SPCL_CHAR)
		return (parse_spcl_char(code, cmd, tk));
	return (tk);
}

/**
 * Use the precedence climbing algorithm to parse the tokens
 * @param code return code
 * @param list of comamnd to init
 * @param tk head of the token list to parse
 * @param prec determine what level of tokens is being treated
 * @return t_token new position in the token list or NULL if a error occurs
*/
static t_token	*prec_climb(t_code *code, t_cmd **cmd, t_token *tk, t_val prec)
{
	return (tk);
	while (tk && tk->val >= prec)
	{
		if (prec != V_SPCL_CHAR && tk->val == prec)
		{
			prec_climb(code, cmd, tk->next, prec + 1);
			if (code != C_SUCCES)
				return (NULL);
		}
		if (tk->val > prec)
			tk = prec_climb(code, cmd, tk, prec + 1);
		if (!tk && *code != C_SUCCES)
			return (NULL);
		tk = parse_tokens(code, cmd, tk, prec);
		if (!tk && *code != C_SUCCES)
			return (NULL);
	}
	return (tk);
}

/**
 * Parse user's input, exit the program if error occurs
 * @param cmd list of comamnd to init
 * @param line pointer to the line to parse
 * @return t_code C_SUCCES or an error code
*/
t_code	parse_line(t_cmd **cmd, char *line)
{
	t_token	*tk;
	t_code	code;

	tk = NULL;
	code = C_SUCCES;
	if (init_tokens(&tk, line))
		exit(clean_memory(C_ERR_MEM, *cmd, line, &tk));
	if (init_spcl_chars(tk))
		return (clean_memory(C_BAD_USE, *cmd, NULL, &tk));
	prec_climb(&code, cmd, tk, V_SEP);
	if (code != C_SUCCES)
		exit(clean_memory(C_ERR_MEM, *cmd, line, &tk));
	return (clean_memory(code, *cmd, NULL, &tk));
}
