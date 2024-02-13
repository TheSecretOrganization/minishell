/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/12 11:09:22 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define CH_ERR "`#()[]{};!\\*"
# define CH_SPCL "&|<>"
# define CH_OPE "&|"
# define CH_DIR "<>"

typedef struct s_ast
{
	char	*next;
	char	*new_i;
	t_cmd	*target;
	size_t	i;
}	t_ast;

t_code	parse_line(t_data *data);

t_code	error_syntax(t_code code, char *el, size_t n);
t_code	check_syntax(t_data *data);
t_code	check_quotes(t_data *data);
t_code	check_spcl_chars(char *line);
t_code	check_in(char *line, size_t *pos, t_bool force_err);
t_code	check_out(char *line, size_t *pos, t_bool force_err);

t_code	expand(t_data *data);
char	*expand_variable(t_data *data, size_t *i);
char	*expand_status(t_data *data);
t_code	expand_var(t_data *data, size_t *i, size_t nd);

t_code	create_ast(t_data *data);
t_code	o_init_cmd(t_cmd **cmd);
t_code	add_ope(t_ast *ast, char *line);
t_code	add_dir(t_ast *ast, char *line);
char	*get_next_substr(t_ast *ast, char *line);
t_code	add_arg(t_ast *ast, char *line);
void	remove_quotes(char **s);

#endif
