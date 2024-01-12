/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 22:18:43 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:32:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Free the allocated memory and exit the program
 * @param code exit code
 * @param cmd list of commands to free
 * @param line pointer on the line to free
 * @param tk list of tokens to free
*/
void	clean_exit(t_code code, t_cmd *cmd, char **line, t_token **tk)
{
	if (cmd)
		(void)cmd;
	if (line && *line)
		free(*line);
	if (tk)
		t_token_clear(tk);
	exit(code);
}
