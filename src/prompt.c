/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:50:14 by averin            #+#    #+#             */
/*   Updated: 2024/01/25 11:22:15 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

/**
 * Send a prompt to the user
 * @param data pointer on where the data is stored
 * @return user's input or NULL if EOT
*/
char	*prompt(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->status)
		data->line = readline("\r\033[K"PROMPT_ERR" "RED"❯ "DEFAULT);
	else
		data->line = readline("\r\033[K"PROMPT_HEAD" "GREEN"❯ "DEFAULT);
	add_history(data->line);
	return (data->line);
}
