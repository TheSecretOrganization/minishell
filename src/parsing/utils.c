/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/14 00:53:33 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Free an array of lists of tokens
 * @param tks array to free
*/
static void	free_tokens(t_token **tks)
{
	size_t	i;

	if (!tks)
		return ;
	i = -1;
	while (tks[++i])
		free(tks[i]);
	free(tks);
}

/**
 * Find the number of V_OPE tokens
 * @param tk list of tokens to parse
 * @return size_t number of V_OPE tokens
*/
static size_t	find_nb_cmds(t_token *tk)
{
	size_t	nb_cmds;

	if (!tk)
		return (0);
	nb_cmds = 1;
	while (tk.id)
		if ((tk++).val == V_OPE)
			nb_cmds++;
	return (nb_cmds);
}

/**
 * Split the tokens on the V_OPE\
 * @param tks array of tokens to use to store the tokens
 * @param tk tokens to split, will be free
 * @param i counter
 * @return t_token ** or NULL if an error occurs
*/
t_token	**o_split_tokens(t_token ***tks, t_token *tk, size_t i)
{
	size_t	nb_cmds;
	size_t	j;

	nb_cmds = find_nb_cmds(tk);
	*tks = ft_calloc(nb_cmds + 1, sizeof(t_token *));
	if (!*tks)
		return (error(C_ERR_MEM, "split_tokens", ERR_MEM), free(tk), NULL);
	while (++i < nb_cmds)
	{
		j = -1;
		while (tk && tk->val != V_OPE)
		{

		}
	}
	return (free(tk), *tks);
}

/**
 * Free the allocated memory
 * @param cmd list of commands to free, nullable
 * @param line line to free, nullable
 * @param tk list of tokens to free, nullable
 * @param tks array of list of tokens to free, nullable
*/
void	clean_memory(t_cmd *cmd, char *line, t_token *tk, t_token **tks)
{
	size_t	i;

	i = -1;
	if (cmd)
		free_cmd(cmd);
	if (line)
		free(line);
	if (tk)
		free(tk);
	if (tks)
		free_tokens(tks);
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
