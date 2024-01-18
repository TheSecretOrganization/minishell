/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:44:23 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/18 15:10:20 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Write error statement to stderr
 * @param code exit code to return
 * @param el element which caused the error, nullable
 * @param message error message details, nullable
 * @return t_code error code
*/
t_code	error(t_code code, char *el, char *message)
{
	ft_putstr_fd(PROMPT_HEAD" :", STDERR_FILENO);
	if (el)
		ft_dprintf(STDERR_FILENO, " %s:", el);
	if (message)
		ft_dprintf(STDERR_FILENO, " %s", message);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (code);
}

/**
 * Free the command and his elements
 * @param cmd command to free
*/
void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	i = -1;
	if (!cmd)
		return ;
	ft_fsplit(cmd->args);
	if (cmd->elements)
	{
		while (cmd->elements[++i])
		{
			if (cmd->elements[i]->type == T_CMD || \
			cmd->elements[i]->type == T_PIPE)
				free_cmd((t_cmd *) cmd->elements[i]->value);
			else
				free(cmd->elements[i]->value);
			free(cmd->elements[i]);
		}
		free(cmd->elements);
	}
	free(cmd);
}

/**
 * Create a new element
 * @param type type of the new element
 * @param value value of the new element
 * @return t_element or NULL if an error occurs
*/
t_element	*new_element(t_type type, void *value)
{
	t_element	*el;

	el = ft_calloc(1, sizeof(t_element));
	if (!el)
		return (NULL);
	el->type = type;
	el->value = value;
	return (el);
}

/**
 * Add a new element to cmd's element array
 * @param cmd
 * @return t_code C_SUCCESS or C_MEM
*/
t_code	addback_cmd(t_cmd *cmd, t_element *el)
{
	size_t		i;
	t_element	**tmp;

	i = -1;
	while (cmd->elements[i])
		i++;
	tmp = ft_calloc(i + 2, sizeof(t_element *));
	if (!tmp)
		return (C_MEM);
	i = -1;
	while (cmd->elements[++i])
		tmp[i] = cmd->elements[i];
	(free(cmd->elements), tmp[i] = el);
	return (cmd->elements = tmp, C_SUCCESS);
}
