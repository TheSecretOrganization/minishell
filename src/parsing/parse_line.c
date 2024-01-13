/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/13 17:17:29 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Tokenize a line
 * @param line line to tokenize
 * @param tk tokens to init
 * @param i counter
 * @return t_code C_SUCCES
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
	return (C_SUCCES);
}

/**
 * Assign the tokens their final values
 * @param tk tokens to check
 * @param i counter
 * @return t_code C_SUCCES or C_BAD_USAGE
*/
static t_code	check_tokens(t_token *tk, size_t i)
{
	size_t	nb[2];

	nb[0] = 0;
	nb[1] = 0;
	while (tk[++i].id)
	{
		if (!(nb[0] % 2) && !(nb[1] % 2) && tk[i].val == V_ERROR)
			return (error_syntax(C_BAD_USE, *tk[i].id));
		else if ((nb[0] % 2 && tk[i].val != V_QUOTE) || \
		(nb[1] % 2 && tk[i].val != V_DQUOTE && tk[i].val != V_VAR))
			tk[i].val = V_CHAR;
		else if (tk[i].val == V_VAR && tk[i + 1].id && tk[i + 1].val == V_CHAR)
			tk[i + 1].val = V_VAR;
		if ((tk[i].val == V_QUOTE && ++(nb[0])) || \
		(tk[i].val == V_DQUOTE && ++(nb[1])))
			;
	}
	if (nb[0] % 2)
		return (error_syntax(C_BAD_USE, '\''));
	else if (nb[1] % 2)
		return (error_syntax(C_BAD_USE, '\"'));
	return (C_SUCCES);
}

/**
 * Parse user's input, exit the program if error occurs
 * @param cmd list of comamnd to init
 * @param line line to parse
 * @return t_code C_SUCCES or an error code
*/
t_code	parse_line(t_cmd **cmd, char *line)
{
	t_token	*tk;
	t_token	**tks;
	size_t	i;

	tk = ft_calloc(ft_strlen(line) + 1, sizeof(t_token));
	if (!tk)
		(clean_memory(*cmd, line, tk, NULL), exit(C_ERR_MEM));
	if (!init_tokens(line, tk, -1) && check_tokens(tk, -1))
		return (clean_memory(*cmd, NULL, tk, NULL), C_BAD_USE);
	printf("%s\n", line);
	i = -1;
	while (tk[++i].id)
		printf("%d", tk[i].val);
	printf("\n");
	if (!o_split_tokens(&tks, tk))
		(clean_memory(*cmd, line, NULL, tks), exit(C_ERR_MEM));
	return (clean_memory(*cmd, NULL, NULL, tks), C_SUCCES);
}
