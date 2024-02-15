/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 08:53:44 by abasdere         ###   ########.fr       */
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
	t_cmd	*target;
	char	**args;
	size_t	i;
	int		status;
	char	**envp;
}	t_ast;

t_code	parse_line(t_data *data);
int		ft_is_space(char c);

t_code	error_syntax(t_code code, char *el, size_t n);
t_code	check_syntax(t_data *data);
t_code	check_quotes(t_data *data);
t_code	check_spcl_chars(char *line);
t_code	check_in(char *line, size_t *pos, t_bool force_err);
t_code	check_out(char *line, size_t *pos, t_bool force_err);

char	*expand_variable(t_data *data, size_t i);
char	*expand_status(t_data *data);
t_code	expand_var(t_data *data, size_t i, size_t nd);

t_code	create_ast(t_data *data);
t_code	o_init_cmd(t_cmd **cmd);
t_code	add_ope(t_ast *ast);
t_code	add_dir(t_ast *ast);
int		remove_and_expand(char **s, t_data *d, int expand, int remove);
char	**split_line(char *line);
void	free_args(t_ast *ast);

#endif
