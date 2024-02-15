/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:48:40 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 14:00:04 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*join_and_replace(char *line, char *td, char *tr, int add_q)
{
	char	*new_tr;
	char	*result;

	if (!add_q)
		return (ft_fstrrplc(line, td, tr));
	new_tr = ft_strjoin("\"", tr);
	if (!new_tr)
		return (NULL);
	new_tr = ft_fstrjoin(new_tr, "\"", 1);
	if (!new_tr)
		return (NULL);
	result = ft_fstrrplc(line, td, new_tr);
	return (free(new_tr), result);
}

static int	chec_perm(char *s, size_t i)
{
	if (i == 0)
		return (1);
	while (--i > 0)
	{
		if (s[i] == '<' && s[i - 1] == '<')
			return (0);
	}
	return (1);
}

/**
 * @brief Remove outer quotes from a line
 *
 * @param d of the program, nullable
 */
int	expand(t_data *d)
{
	t_quotes	q;
	size_t		i;

	q.nd = 0;
	q.nq = 0;
	i = -1;
	while (d->line[++i])
	{
		if (!(q.nq % 2) && (d->line[i] == '$'
				&& (d->line[i + 1] == '?' || ft_isalpha(d->line[i + 1])))
			&& chec_perm(d->line, i))
		{
			if (expand_var(d, i))
				return (C_MEM);
			i--;
			continue ;
		}
		if (d->line[i] == '\'' && !(q.nd % 2))
			(q.nq)++;
		else if (d->line[i] == '\"' && !(q.nq % 2))
			(q.nd)++;
	}
	return (C_SUCCESS);
}
