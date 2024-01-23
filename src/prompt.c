/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:50:14 by averin            #+#    #+#             */
/*   Updated: 2024/01/23 11:06:40 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

/**
 * Send a prompt to the user
 * @param line pointer on where to store the inout
 * @param status status code return by the last command
 * @return user's input or NULL if EOT
*/
char	*prompt(char **line, int status)
{
	if (*line)
		free(*line);
	if (status)
		*line = readline(PROMPT_ERR" "RED"❯ "DEFAULT);
	else
		*line = readline(PROMPT_HEAD" "GREEN"❯ "DEFAULT);
	add_history(*line);
	return (*line);
}
