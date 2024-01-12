/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:50:14 by averin            #+#    #+#             */
/*   Updated: 2024/01/12 10:17:43 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

/**
 * Send a prompt to the user
 * @return user's input or NULL if EOT
*/
char	*prompt(char **line)
{
	if (*line)
		free(*line);
	*line = readline("🦖 "GREEN"❯ "DEFAULT);
	add_history(*line);
	return (*line);
}
