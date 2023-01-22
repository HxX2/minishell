/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:38:16 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/22 13:50:57 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTER_H
# define EXECUTER_H
# include "../minishell.h"	

typedef struct s_envn
{
	char			*key;
	char			*value;
	struct s_envn	*next;
}			t_envl;

void	set_envval(char *key, char *new_val);
void 	env_push(t_envl **lst, t_envl *new);
char	*get_envval(char *env_var);
t_envl	*new_envp(char *env_var);
t_envl	*get_env(char *env_var);
void 	set_envp(char **envp);
int		is_valid_id(char *id);
void	exe_cmd(char **args);
int		envp_size(void);
void	env_cast(void);
void	signals(void);
char	*ps1();

char	*ft_joinpath(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_rwipe(void *ptr, int plvl);
void	*ft_xalloc(size_t n);

void	ft_exit(char **args);
void	export(char **args);
void	unset(char **args);
void	echo(char **args);
void 	cd(char **args);
void	env(void);
void	pwd(void);

#endif