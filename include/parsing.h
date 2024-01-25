/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/25 17:05:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define CH_ERR "`#()\\[]{};!"
# define CH_SPCL "&|<>"
# define CH_OPE "&|"
# define CH_DIR "<>"

typedef struct s_ast
{
	int		status;
	char	*j_args;
	char	*next;
	t_cmd	*target;
	size_t	i;
}	t_ast;

t_code	parse_line(t_data *data);

t_code	check_quotes(char *line);
t_code	check_syntax(t_data *data);
t_code	check_spcl_chars(char *line);
t_code	check_pipe(char *line, size_t pos);
t_code	check_ampersand(char *line, size_t pos);
t_code	error_syntax(t_code code, char *el, size_t n);

char	*expand_variables(char *line, int status);

t_code	create_ast(t_data *data);

t_code	add_ope(t_ast *ast, char *line);
t_code	o_init_cmd(t_cmd **cmd);

t_code	add_dir(t_ast *ast, char *line);

char	*find_next_sep(char *line);
t_code	join_args(t_ast *ast, char *line);
t_code	split_args(t_ast *ast);

#endif
