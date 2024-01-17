/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_split_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:02:23 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/17 14:51:10 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	while (tk->id)
	{
		if ((tk++)->val == V_OPE && ++nb_cmds)
			while (tk->id && tk->val == V_OPE)
				tk++;
	}
	return (nb_cmds);
}

static t_token	*get_next_ope_index(t_token *tk)
{
	while (tk && tk->id)
	{
		if (tk->val == V_OPE)
		{
			while (tk && tk->val == V_OPE)
				tk++;
			return (tk - 1);
		}
		tk++;
	}
	return (tk);
}

static t_token	*sub_tokens(t_token *start, t_token *end)
{
	t_token	*dup;
	size_t	i;
	size_t	len;

	i = -1;
	len = end - start;
	dup = ft_calloc(len + 1, sizeof(t_token));
	if (!dup)
		return (error(C_MEM, "sub_tokens", M_MEM), NULL);
	while (++i < len)
	{
		dup[i].id = start->id;
		dup[i].val = (start++)->val;
	}
	return (dup);
}

/**
 * Free an array of lists of tokens
 * @param tks array to free
*/
void	free_tokens(t_token **tks)
{
	size_t	i;

	if (!tks)
		return ;
	i = -1;
	while (tks[++i])
		(free(tks[i]), tks[i] = NULL);
	(free(tks), tks = NULL);
}

/**
 * Split the tokens on the V_OPE\
 * @param tks array of tokens to use to store the tokens
 * @param tk tokens to split
 * @param line line to free if an error occurs
 * @return t_code C_SUCCESS or an error
*/
t_code	o_split_tokens(t_token ***tks, t_token *tk, char *line)
{
	size_t	i;
	size_t	nb_cmds;
	t_token	*next;

	i = -1;
	nb_cmds = find_nb_cmds(tk);
	if (!nb_cmds)
		return (C_BAD_USE);
	*tks = ft_calloc(nb_cmds + 1, sizeof(t_token *));
	if (!*tks)
		(clean_memory(NULL, line, tk, *tks), \
		exit(error(C_MEM, "o_split_tokens", M_MEM)));
	while (++i < nb_cmds)
	{
		next = get_next_ope_index(tk);
		(*tks)[i] = sub_tokens(tk, next);
		if (!(*tks)[i])
			(clean_memory(NULL, line, tk, *tks), exit(C_MEM));
		tk = NULL;
		if (next)
			tk = next + 1;
	}
	return (C_SUCCESS);
}
