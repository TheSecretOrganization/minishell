/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:16:34 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_val
{
	ERROR = 0,
	CHAR = 1,
	SEP = 2,
	WILDCARD = 3,
	VARIABLE = 4,
	QUOTE = 5,
	D_QUOTE = 6,
	SPCL_CHAR = 7
}	t_val;

typedef struct s_token
{
	t_val			val;
	char			*id;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	t_token_addback(t_token **lst, t_token *new);
void	t_token_clear(t_token **lst);
void	t_token_delone(t_token *lst);
t_token	*t_token_last(t_token *lst);
t_token	*t_token_new(char *id);
void	t_token_print_vals(t_token *lst);
size_t	t_token_size(t_token *lst);

void	clean_exit(t_code code, t_cmd *cmd, char **line, t_token **lst);
void	parse_line(t_cmd *cmd, char **line);

#endif
