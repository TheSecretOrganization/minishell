/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:50:14 by averin            #+#    #+#             */
/*   Updated: 2024/01/10 13:57:11 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

/**
 * Prompt the user 
 * @return user's input or NULL if EOT
*/
char	*prompt(char **line)
{
	if (!*line)
		free(*line);
	*line = readline("🦕 "GREEN"❯ "DEFAULT);
	add_history(*line);
	return (*line);
}
