/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:17:31 by averin            #+#    #+#             */
/*   Updated: 2024/02/15 23:31:02 by abasdere         ###   ########.fr       */
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
	int		i;
	t_data	*data;
	t_cmd	*target;
}	t_exec;

int		dispatch_cmd(t_data *data);
void	do_exec(t_exec *exec, char **envp, int *pid);
char	*find_pathname(t_exec *exec, char **path);
int		get_path(t_data *data);
int		fill_exec(t_exec *exec, t_cmd cmd, char **path);
void	*find_element(t_cmd cmd, t_type type);
int		for_redirections(t_cmd cmd, t_exec *exec, int (*in)(void *, t_exec *),
			int (*out)(void *, t_exec *));
void	init_exec(t_exec *exec, t_data *data);
void	reset_exec(t_exec *exec);
int		wait_children(int pid);

int		here_doc(t_exec *exec, char *delimiter);
char	*find_heredoc_file(char c);
int		setup_here_doc(t_exec *exec);

int		init_pipe(t_cmd *cmd, t_exec *exec);
int		init_redirections(t_cmd cmd, t_exec *exec);

int		exec_builtin(t_exec *exec);
int		is_builtin(t_cmd cmd, t_exec *exec);

#endif
