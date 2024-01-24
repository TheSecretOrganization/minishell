/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:08:16 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/24 19:56:10 by abasdere         ###   ########.fr       */
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
	t_code	code;

	code = check_syntax(data);
	if (code == C_BAD_USE)
		return (free(data->line), data->line = NULL, C_BAD_USE);
	else if (code == C_MEM)
		(clean_data(data), exit(C_MEM));
	code = create_ast(data);
	if (code == C_BAD_USE)
		return (free(data->line), data->line = NULL, C_BAD_USE);
	else if (code == C_MEM)
		(clean_data(data), exit(C_MEM));
	return (free(data->line), data->line = NULL, C_SUCCESS);
}
