/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:44:23 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 20:30:26 by abasdere         ###   ########.fr       */
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
