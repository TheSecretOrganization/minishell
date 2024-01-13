/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/13 17:17:32 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_val
{
	V_ERROR = 0,
	V_SEP = 1,
	V_CHAR = 2,
	V_WLDCRD = 3,
	V_VAR = 4,
	V_QUOTE = 5,
	V_DQUOTE = 6,
	V_REDIR = 7,
	V_OPE = 8
}	t_val;

typedef struct s_token
{
	char	*id;
	t_val	val;
}	t_token;

void	clean_memory(t_cmd *cmd, char *line, t_token *tk, t_token **tks);
t_code	error_syntax(t_code code, char el);
t_code	parse_line(t_cmd **cmd, char *line);

#endif
