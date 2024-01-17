/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/17 16:11:21 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Tokenize a line
 * @param line line to tokenize
 * @param tk tokens to init
 * @param i counter
 * @return t_code C_SUCCESS
 * */
static t_code	init_tokens(char *line, t_token *tk, size_t i)
{
	while (line[++i])
	{
		tk[i].id = &line[i];
		if (ft_strchr("~`#()\\[]{};?!", line[i]))
			tk[i].val = V_ERROR;
		else if (ft_strchr("&|", line[i]))
			tk[i].val = V_OPE;
		else if (ft_strchr("<>", line[i]))
			tk[i].val = V_REDIR;
		else if (line[i] == '\"')
			tk[i].val = V_DQUOTE;
		else if (line[i] == '\'')
			tk[i].val = V_QUOTE;
		else if (line[i] == '$')
			tk[i].val = V_VAR;
		else if (line[i] == '*')
			tk[i].val = V_WLDCRD;
		else if (line[i] == ' ')
			tk[i].val = V_SEP;
		else
			tk[i].val = V_CHAR;
	}
	tk[i].id = NULL;
	tk[i].val = -1;
	return (C_SUCCESS);
}

/**
 * Deal with V_OPE tokens errors
 * @param code error code to return
 * @param tk tokens to compute
 * @return t_code error code
*/
static t_code	error_ope(t_code code, t_token *tk)
{
	if (!tk)
		return (code);
	if (tk + 1 && (tk + 1)->val == V_OPE)
		if (*tk->id == '|' || *(tk + 1)->id == '&')
			return (error_syntax(code, tk->id, 2));
	return (error_syntax(code, tk->id, 1));
}

/**
 * Check the syntax of the V_OPE tokens
 * @param tk tokens to check
 * @return t_code C_SUCCESS or C_BAD_USAGE
*/
static t_code	check_ope(t_token **tk, size_t *x)
{
	while (tk && *tk && (*tk)->val == V_OPE)
	{
		if (!*x)
			return (error_ope(C_BAD_USE, *tk));
	}
	return (*x = 0, C_SUCCESS);
}

/**
 * Assign the tokens their final values
 * @param tk tokens to check
 * @param nq number of quotes
 * @param nd number of double quotes
 * @param x syntax checker
 * @return t_code C_SUCCESS or C_BAD_USAGE
*/
static t_code	check_tokens(t_token *tk, size_t nq, size_t nd, size_t x)
{
	while (tk->id)
	{
		if (!(nq % 2) && !(nd % 2) && tk->val == V_ERROR)
			return (error_syntax(C_BAD_USE, &(*tk->id), 1));
		else if ((nq % 2 && tk->val != V_QUOTE) || \
		(nd % 2 && tk->val != V_DQUOTE && tk->val != V_VAR))
			tk->val = V_CHAR;
		else if (tk->val == V_VAR && (tk + 1)->id && (tk + 1)->val == V_CHAR)
			(tk + 1)->val = V_VAR;
		if ((tk->val == V_QUOTE && ++(nq)) || \
		(tk->val == V_DQUOTE && ++(nd)))
			;
		if (tk->val == V_CHAR || tk->val == V_VAR)
			x++;
		if (tk->val == V_OPE && check_ope(&tk, &x))
			return (C_BAD_USE);
		tk++;
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}

/**
 * Parse user's input, exit the program if error occurs
 * @param cmd list of comamnd to init
 * @param line line to parse
 * @return t_code C_SUCCESS or an error code
*/
t_code	parse_line(t_cmd **cmd, char *line)
{
	t_token	**tks;
	t_token	*tk;

	tks = NULL;
	tk = ft_calloc(ft_strlen(line) + 1, sizeof(t_token));
	if (!tk)
		(free(line), exit(error(C_MEM, "ft_calloc", M_MEM)));
	if (!init_tokens(line, tk, -1) && check_tokens(tk, 0, 0, 0))
		return (clean_memory(*cmd, line, tk, tks), C_BAD_USE);
	if (o_split_tokens(&tks, tk, line))
		return (clean_memory(*cmd, line, tk, tks), C_BAD_USE);
	free(tk);
	if (create_cmds(cmd, tks, line))
		return (clean_memory(*cmd, line, NULL, tks), C_BAD_USE);
	return (clean_memory(NULL, line, NULL, tks), C_SUCCESS);
}
