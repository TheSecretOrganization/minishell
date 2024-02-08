/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:30 by averin            #+#    #+#             */
/*   Updated: 2024/02/08 12:18:49 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "libft.h"

# define PROMPT_HEAD "🦖"
# define PROMPT_ERR "☄️"

# define M_ERROR "error"
# define M_MEM "memory allocation failled"

typedef enum e_code
{
	C_SUCCESS = 0,
	C_GEN,
	C_BAD_USE,
	C_MEM,
	C_NOFILE,
	C_NOEXEC
}	t_code;

typedef enum e_type
{
	T_CMD = 1,
	T_INFILE = 2,
	T_OUTFILE = 3,
	T_PIPE = 4,
	T_PIPE_AND = 5,
	T_PIPE_OR = 6
}	t_type;

typedef enum e_outtype
{
	OT_TRUNCATE = 1,
	OT_APPEND
}	t_outtype;

typedef enum e_intype
{
	IT_INFILE = 1,
	IT_HERE_DOC,
	IT_CREATE
}	t_intype;

typedef struct s_element
{
	t_type	type;
	void	*value;
}	t_element;

typedef struct s_infile
{
	char		*filename;
	t_intype	intype;
}	t_infile;

typedef struct s_outfile
{
	char		*filename;
	t_outtype	outtype;
}	t_outfile;

typedef struct s_cmd
{
	char		**args;
	t_element	**elements;
}	t_cmd;

typedef struct s_data
{
	char	**envp;
	char	*line;
	t_cmd	*cmd;
	char	**path;
	int		status;
}	t_data;

extern int	g_signal;

t_code		error(t_code code, char *el, char *message);
void		clean_data(t_data *data);
void		free_cmd(t_cmd *cmd);
char		*prompt(t_data *data);
void		register_signals(void);

t_code		addback_cmd(t_cmd *cmd, t_element *el);
t_element	*new_element(t_type type, void *value);

int			here_doc(t_exec *exec, char *delimiter);

char		*ft_getenv(t_data data, char *item);
t_code		ft_setenv(t_data *data, char *item, char *value);
t_code		ft_unenv(t_data *data, char *item);
t_code		cpy_envp(t_data *data, char **envp);

#endif
