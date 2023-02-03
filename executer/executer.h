/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:38:16 by zlafou            #+#    #+#             */
/*   Updated: 2023/02/03 20:45:44 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H
# include "../minishell.h"	

typedef struct s_vect
{
	int	in;
	int	out;
}		t_vect;

void	dup_red_pipe(t_execcmd *cmd, int in, int out);
char	*ft_joinpath(char const *s1, char const *s2);
void	close_io(t_execcmd *cmd);
void	exe_cmd(t_execcmd *cmd, int in, int out, int *p);
void	set_envval(char *key, char *new_val);
void	env_push(t_envl **lst, t_envl *new);
void	exec_builtins(t_execcmd *x_cmd);
void	ft_rwipe(void *ptr, int plvl);
char	*get_envval(char *env_var);
t_envl	*new_envp(char *env_var);
t_envl	*get_env(char *env_var);
void	set_envp(char **envp);
int		is_valid_id(char *id);
void	*ft_xalloc(size_t n);
int		envp_size(void);
void	env_cast(void);
void	ch_signals(void);
char	*ps1(void);

void	ft_exit(char **args);
void	export(char **args);
void	unset(char **args);
void	echo(char **args);
void	cd(char **args);
void	env(void);
void	pwd(void);

#endif