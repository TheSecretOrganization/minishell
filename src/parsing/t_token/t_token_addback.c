/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:53:42 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/11 12:50:24 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Add a new node at the end of a t_token list
 * @param lst list to add the node to
 * @param new node to add
*/
void	t_token_addback(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = t_token_last(*lst);
	last->next = new;
	new->prev = last;
	new->next = NULL;
}
