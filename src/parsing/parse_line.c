/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/24 13:56:55 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Parse user's input, exit the program if error occurs
 * @param data pointer on where the data is stored
 * @return t_code C_SUCCESS or an error code
*/
t_code	parse_line(t_data *data)
{
	if (check_syntax(data))
		return (C_BAD_USE);
	if (create_ast(data))
		return (C_BAD_USE);
	(free(data->line), data->line = NULL);
	return (C_SUCCESS);
}
