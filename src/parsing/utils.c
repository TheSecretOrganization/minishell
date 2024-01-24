/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/24 19:52:37 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Free the allocated memory
 * @param data pointer on where the data is stored
*/
void	clean_data(t_data *data)
{
	if (data->cmd)
		(free_cmd(data->cmd), data->cmd = NULL);
	if (data->line)
		(free(data->line), data->line = NULL);
	if (data->path)
		(free(data->path), data->path = NULL);
}

/**
 * Catenate a space and n char from one string to another
 * @param s1 destination string, will be free
 * @param s2 source string
 * @param n number of char to catenate
 * @return char * or NULL if an error occurs
*/
char	*fspace_njoin(char *s1, char *s2, size_t n)
{
	size_t	len;
	size_t	i;
	char	*join;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	join = ft_calloc(len + n + 2, sizeof(char));
	if (!join)
		return (free(s1), s1 = NULL, error(C_MEM, "ft_calloc", M_MEM), NULL);
	i = -1;
	while (++i < len)
		join[i] = s1[i];
	join[len] = ' ';
	i = -1;
	while (++i < n)
		join[len + 1 + i] = s2[i];
	return (free(s1), s1 = NULL, join);
}

/**
 * Find the next separator in a line
 * @param line line to check
 * @return char * to the next seprator
*/
char	*find_next_sep(char *line)
{
	if (!line)
		return (NULL);
	while (*line)
	{
		if (ft_strchr(CH_DIR, *line) || ft_strchr(CH_OPE, *line)
			|| *line == ' ')
			return (line);
		line++;
	}
	return (line);
}
