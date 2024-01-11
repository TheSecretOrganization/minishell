/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:59:18 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/11 12:45:36 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


/**
 * Delete a t_token list
 * @param lst node to destroy
*/
void	t_token_clear(t_token **lst)
{
	if (!lst || !(*lst))
		return ;
	if ((*lst)->next)
		t_token_clear(&(*lst)->next);
	t_token_delone(*lst);
	*lst = NULL;
}
