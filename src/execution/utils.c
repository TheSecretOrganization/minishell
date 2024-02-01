/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:03:13 by averin            #+#    #+#             */
/*   Updated: 2024/02/01 12:28:26 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * @brief Initialize exec with default values
 * 
 * @param exec pointer to exec to init
 */
void	init_exec(t_exec *exec)
{
	exec->pathname = NULL;
	exec->infile = -1;
	exec->outfile = -1;
	exec->pipes[0] = -1;
	exec->pipes[1] = -1;
}

/**
 * Init the exec structure
 * @param exec structure to init
 * @param cmd cmd to init from
 * @param path the path
 * @return SUCCESS or corresponding exit code 
*/
int	fill_exec(t_exec *exec, t_cmd cmd, char **path)
{
	exec->args = cmd.args;
	if (exec->pathname)
		free(exec->pathname);
	exec->pathname = NULL;
	if (cmd.args[0] != NULL && !find_pathname(exec, path))
	{
		if (errno == C_NOEXEC)
			return (printf("%s: No permission\n", exec->args[0]), 127);
		else if (errno == C_NOFILE)
			return (printf("%s: Not found\n", exec->args[0]), 126);
	}
	return (C_SUCCESS);
}

/**
 * Find an element and return his value
 * @param cmd cmd in wich search the element
 * @param type type of the element to search
 * @return element's value or NULL if not found
*/
void	*find_element(t_cmd cmd, t_type type)
{
	size_t	i;

	i = -1;
	while (cmd.elements[++i])
	{
		if (cmd.elements[i]->type == type)
			return (cmd.elements[i]->value);
	}
	return (NULL);
}
