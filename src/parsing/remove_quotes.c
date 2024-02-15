/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:12:34 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 14:33:29 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check here_doc permission
 *
 * @param s string to parse
 * @param i position in s
 * @return int
 */
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
	if (!q->e && s[i] == '\"' && !(q->nq % 2) && !(q->nd % 2) 
		&& i > 0 && s[i - 1] == '=')
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
int	remove_quotes(char *s)
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
