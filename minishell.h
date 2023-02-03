/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:11:41 by aamoussa          #+#    #+#             */
/*   Updated: 2023/02/03 20:41:41 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft/libft.h"
# define EXEC  1
# define REDIR 2
# define PIPE  3
# define BLUE "\033[0;35m"
# define PURPLE "\033[0;34m"
# define RESET "\033[0;0m"

typedef struct s_envn
{
	char			*key;
	char			*value;
	struct s_envn	*next;
}			t_envl;

typedef struct s_gb_variable
{
	char	**envp;
	t_envl	*env;
	int		last_fd;
	int		status;
	int		exit_statut;
	int		npipe;
	int		fd_input_prev;
	pid_t	last_pid;
	int		input;
	int		output;
	int		here_doc;
	char	*curent;
}	t_gb_variable;

t_gb_variable	g_gb;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd {
	int		type;
	t_list	*args;
	int		output;
	int		input;
	char	**argument;		
}	t_execcmd;

typedef struct s_pipecmd {
	int		type;
	int		*std;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

void	leave(void);
void	free_cmd(t_cmd *cmd);
int		is_builtin(t_execcmd *x_cmd);
void	exec_builtins(t_execcmd *x_cmd);
void	n_pipe(t_cmd *cmd, int in, int out, int *p);
t_cmd	*parser(char **ps, char *es, char **envp);
void	rl_replace_line(const char *text, int clear_undo);
int		ft_strcmp(const char *s1, const char *s2);
void	waitproc(void);
void	signals(void);
#endif