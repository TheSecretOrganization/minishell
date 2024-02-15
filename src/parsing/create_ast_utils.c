/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 08:35:48 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_args(t_ast *ast)
{
	size_t	i;

	i = -1;
	while (ast->args[ast->i + ++i])
		free(ast->args[ast->i]);
	free(ast->args);
}

/**
 * @brief Find the next argument in line
 *
 * @param line line to parse
 * @param end pointer on the end of the arg
 * @return char* start of the next arg
 */
static char	*find_next_arg(char *line, char **end)
{
	char	c;

	c = '\0';
	while (*line && ft_is_space(*line))
		line++;
	if (!*line)
		return (*end = line, line);
	*end = line;
	if (**end != '\0' && ft_strchr(CH_SPCL, *line))
		while (**end != '\0' && ft_strchr(CH_SPCL, **end))
			(*end)++;
	else
	{
		while (**end != '\0')
		{
			if (!c && (**end == '\'' || **end == '\"'))
				c = **end;
			else if (c && **end == c)
				c = '\0';
			if (!c && (ft_is_space(**end) || ft_strchr(CH_SPCL, **end)))
				break ;
			(*end)++;
		}
	}
	return (line);
}

/**
 * @brief Get the next substr object
 *
 * @param line line parsed
 * @param end pointer on the end of str
 * @return char* or NULL
 */
static char	*get_next_substr(char *line, char **end)
{
	char	*sub;
	char	*start;

	start = find_next_arg(line, end);
	sub = ft_substr(line, start - line, *end - start);
	if (!sub)
		return (error(C_MEM, "ft_substr", M_MEM), NULL);
	return (sub);
}

size_t	count_args(char *line)
{
	size_t	i;
	char	*end;

	i = 0;
	while (*line)
	{
		end = NULL;
		i++;
		(find_next_arg(line, &end), line = end);
	}
	return (i);
}

char	**split_line(char *line)
{
	size_t	i;
	size_t	cw;
	char	*end;
	char	**args;

	i = -1;
	cw = count_args(line);
	end = NULL;
	args = ft_calloc(cw + 1, sizeof(char *));
	if (!args)
		return (error(C_MEM, "ft_calloc", M_MEM), NULL);
	while (*line && ++i < cw)
	{
		args[i] = get_next_substr(line, &end);
		if (!args[i])
			return (ft_fsplit(args), NULL);
		line = end;
	}
	return (args);
}
