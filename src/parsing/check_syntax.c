/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:54:29 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 11:29:44 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check if all quotes are closed in the line
 *
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or an error
 */
static t_code	check_quotes(t_data *data)
{
	size_t	nq;
	size_t	nd;
	size_t	i;

	nq = 0;
	nd = 0;
	i = -1;
	while (data->line[++i])
	{
		if (!(nq % 2) && !(nd % 2) && ft_strchr(CH_ERR, data->line[i]))
			return (error_syntax(C_BAD_USE, &(data->line[i]), 1));
		if (data->line[i] == '\'' && !(nd % 2))
			nq++;
		if (data->line[i] == '\"' && !(nq % 2))
			nd++;
	}
	if (nq % 2)
		return (error_syntax(C_BAD_USE, "\'", 1));
	else if (nd % 2)
		return (error_syntax(C_BAD_USE, "\"", 1));
	return (C_SUCCESS);
}

int	check_hd(char *s, size_t i)
{
	if (s[i++] != '<')
		return (0);
	if (s[i++] != '<')
		return (0);
	while (s[i] && ft_is_space(s[i]))
		i++;
	if (s[i] == '\'' || s[i] == '\"')
		return (1);
	return (0);
}

/**
 * @brief Set the quotes permissions
 *
 * @param s string to check
 * @param q data of the quotes
 * @param i position in string
 * @return int
 */
static int	set_perm(char *s, t_quotes *q, size_t i)
{
	if (!q->e && s[i] == '\"' && !(q->nq % 2) && i > 0 && s[i - 1] == '=')
		return (q->e = 1, 0);
	else if (q->e && s[i] == '\"' && !(q->nq % 2) && (q->nd)++ % 2)
		return (q->e = 0, 1);
	if (!q->h && check_hd(s, i))
		return (q->h = 1, 0);
	else if (q->h && s[i] == '\"' && !(q->nq % 2) && (q->nd)++ % 2)
		return (q->h = 0, 1);
	return (0);
}

/**
 * @brief Remove outer quotes from a line
 *
 * @param s pointer on the string to trim
 */
static int	remove_quotes(char *s)
{
	size_t		i;
	size_t		len;
	t_quotes	q;

	i = -1;
	len = ft_strlen(s);
	q.nd = 0;
	q.nq = 0;
	q.e = 0;
	q.h = 0;
	while (++i < len)
	{
		if (set_perm(s, &q, i))
			continue ;
		if ((s[i] == '\'' && !(q.nd % 2) && ++(q.nq) && !q.h)
			|| (s[i] == '\"' && !(q.nq % 2) && ++(q.nd) && !q.e && !q.h))
		{
			ft_memcpy(&(s[i]), &(s[i + 1]), len - i);
			len--;
			i--;
		}
	}
	return (C_SUCCESS);
}

/**
 * Check bash syntax in one line
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or C_BAD_USE
*/
t_code	check_syntax(t_data *data)
{
	if (check_quotes(data) || check_spcl_chars(data->line))
		return (C_BAD_USE);
	if (expand(data))
		return (C_MEM);
	return (remove_quotes(data->line));
}
