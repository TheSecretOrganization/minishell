/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/22 09:45:56 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Parse user's input, exit the program if error occurs
 * @param cmd list of comamnd to init
 * @param line line to parse
 * @return t_code C_SUCCESS or an error code
*/
t_code	parse_line(t_cmd **cmd, char *line)
{
	if (!line || !*line)
		return (C_SUCCESS);
	if (check_syntax(line))
		return (C_BAD_USE);
	if (create_ast(cmd, line))
		return (C_BAD_USE);
	return (C_SUCCESS);
}
