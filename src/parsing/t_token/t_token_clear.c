/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:59:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:33:51 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Delete a t_token list
 * @param tk node to destroy
*/
void	t_token_clear(t_token **tk)
{
	if (!tk || !(*tk))
		return ;
	if ((*tk)->next)
		t_token_clear(&(*tk)->next);
	free(*tk);
	*tk = NULL;
}
