/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/13 00:39:29 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Free the allocated memory
 * @param code return code
 * @param cmd list of commands to free, nullable
 * @param line line to free, nullable
 * @param tk list of tokens to free, nullable
 * @return t_code
*/
t_code	clean_memory(t_code code, t_cmd *cmd, char *line, t_token *tk)
{
	if (cmd)
		free_cmd(cmd);
	if (line)
		free(line);
	if (tk)
		free(tk);
	return (code);
}

/**
 * Write error statement to stderr
 * @param code exit code to return
 * @param el element which caused the error, nullable
 * @return t_code error code
*/
t_code	error_syntax(t_code code, char el)
{
	ft_putstr_fd(PROMPT_HEAD":", STDERR_FILENO);
	if (el)
		ft_dprintf(STDERR_FILENO, \
		" syntax error near unexpected token `%c'", el);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (code);
}

/**
 * Parse in function of their precedence
 * @param code return code
 * @param list of comamnd to init
 * @param tk head of the token list to parse
 * @param prec determine what level of tokens is being treated
 * @return t_token new position in the token list or NULL if a error occurs
*/
// t_token	*parse_tokens(t_code *code, t_cmd **cmd, t_token *tk, t_val prec)
// {
// 	if (prec == V_SEP)
// 		while (tk && tk->val == V_SEP)
// 			tk = tk->next;
// 	else if (prec == V_CHAR)
// 		;
// 	else if (prec == V_WLCRD)
// 		return (error_syntax(C_BAD_USE, '*'), NULL);
// 	else if (prec == V_VAR)
// 		;
// 	else if (prec == V_QUOTE)
// 		;
// 	else if (prec == V_DQUOTE)
// 		;
// 	else if (prec == V_SPCL_CHAR)
// 		return (parse_spcl_char(code, cmd, tk));
// 	return (tk);
// }

/**
 * Use the precedence climbing algorithm to parse the tokens
 * @param code return code
 * @param list of comamnd to init
 * @param tk head of the token list to parse
 * @param prec determine what level of tokens is being treated
 * @return t_token new position in the token list or NULL if a error occurs
*/
// static t_token	*prec_climb(t_code *code, t_cmd **cmd, t_token *tk, t_val prec)
// {
// 	return (tk);
// 	while (tk && tk->val >= prec)
// 	{
// 		if (prec != V_SPCL_CHAR && tk->val == prec)
// 		{
// 			prec_climb(code, cmd, tk->next, prec + 1);
// 			if (code != C_SUCCES)
// 				return (NULL);
// 		}
// 		if (tk->val > prec)
// 			tk = prec_climb(code, cmd, tk, prec + 1);
// 		if (!tk && *code != C_SUCCES)
// 			return (NULL);
// 		tk = parse_tokens(code, cmd, tk, prec);
// 		if (!tk && *code != C_SUCCES)
// 			return (NULL);
// 	}
// 	return (tk);
// }

// t_code	init_cmd(t_cmd **cmd, t_token *tk)
// {
// 	size_t	nb_cmd;

// 	nb_cmd = 1;
// 	while (tk)
// 	{
// 		if (tk->val == V_OPE && tk->next && tk->next->val != V_OPE)
// 			nb_cmd++;
// 		tk = tk->next;
// 	}
// 	*cmd = ft_calloc(sizeof)
// }
