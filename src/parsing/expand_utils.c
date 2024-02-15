/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:48:40 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 12:58:16 by abasdere         ###   ########.fr       */
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
		if (!(q.nq % 2) && !check_hd(d->line, i)
			&& ((d->line[i] == '$' && d->line[i + 1])
				|| (d->line[i] == '~' && !(q.nd % 2)
					&& ft_is_space(d->line[i + 1]))))
		{
			if (expand_var(d, i, q.nd))
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
