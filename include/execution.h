/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:17:31 by averin            #+#    #+#             */
/*   Updated: 2024/02/01 22:42:42 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <errno.h>

typedef struct s_exec
{
	char	**args;
	char	*pathname;
	int		pipes[2];
	int		infile;
	int		outfile;
	int		is_builtin;
	int		(*builtin)(struct s_exec *);
	int		is_pipe;
	t_data	*data;
	t_cmd	*target;
}	t_exec;

int		dispatch_cmd(t_data *data);
int		do_exec(t_exec *exec, char **envp);
char	*find_relative_exec(char *cmd);
char	*find_path_exec(char *cmd, char **path);
char	**get_path(void);
int		fill_exec(t_exec *exec, t_cmd cmd, char **path);
void	*find_element(t_cmd cmd, t_type type);
void	init_exec(t_exec *exec, t_data *data);
int		wait_children(int pid);

int		exec_builtin(t_exec *exec);
int		is_builtin(t_cmd cmd, t_exec *exec);

#endif
