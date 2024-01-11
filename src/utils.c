/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:44:23 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/11 18:50:38 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Write error statement to stderr
 * @param el element which caused the error
 * @param message error message details
 * @return int error code
*/
int	error(char *el, char *message)
{
	ft_dprintf(STDERR_FILENO, "%s: %s", el, message);
	return (EXIT_FAILURE);
}
