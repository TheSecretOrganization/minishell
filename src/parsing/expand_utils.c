/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:48:40 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 11:28:46 by abasdere         ###   ########.fr       */
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
	size_t	nq;
	size_t	nd;
	size_t	i;

	nd = 0;
	nq = 0;
	i = -1;
	while (d->line[++i])
	{
		if (!(nq % 2) && check_hd(d->line, i)
			&& ((d->line[i] == '$' && d->line[i + 1])
				|| (d->line[i] == '~' && !(nd % 2)
					&& ft_is_space(d->line[i + 1]))))
		{
			if (expand_var(d, i, nd))
				return (C_MEM);
			i--;
			continue ;
		}
		if (d->line[i] == '\'' && !(nd % 2))
			++nq;
		else if (d->line[i] == '\"' && !(nq % 2))
			++nd;
	}
	return (C_SUCCESS);
}
