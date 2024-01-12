/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_print_vals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:15:27 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:16:36 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Print all vals of a t_token list
 * @param lst list to print
*/
void	t_token_print_vals(t_token *lst)
{
	while (lst)
	{
		printf("%d", lst->val);
		lst = lst->next;
	}
	printf("\n");
}
