/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 09:36:31 by zlafou            #+#    #+#             */
/*   Updated: 2023/02/03 20:48:05 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

char	**get_paths(char *path)
{
	char	**paths;

	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

char	*get_cmd_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	else
	{
		paths = get_paths(get_envval("PATH"));
		i = 0;
		while (paths[i])
		{
			path = ft_joinpath(paths[i], cmd);
			if (!access(path, F_OK))
			{
				ft_rwipe(paths, 2);
				return (path);
			}
			else
				free(path);
			i++;
		}
	}
	ft_rwipe(paths, 2);
	return (NULL);
}

static	int	throw_error(char *cmd, char	*path)
{
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_gb.exit_statut = 127;
		return (1);
	}
	if (access(path, F_OK | R_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_gb.exit_statut = 127;
		return (1);
	}
	if (access(path, X_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_gb.exit_statut = 126;
		return (1);
	}
	return (0);
}

void	child_proc(char *cmdpath, t_execcmd *cmd, t_vect pip, int *p)
{
	ch_signals();
	dup_red_pipe(cmd, pip.in, pip.out);
	if (p)
	{
		close(p[0]);
		close(p[1]);
	}
	if (is_builtin(cmd))
	{
		exec_builtins(cmd);
		exit(g_gb.exit_statut);
	}
	else
		execve(cmdpath, cmd->argument, g_gb.envp);
}

void	exe_cmd(t_execcmd *cmd, int in, int out, int *p)
{
	char	*cmdpath;
	t_vect	pip;

	pip.in = in;
	pip.out = out;
	cmdpath = get_cmd_path(cmd->argument[0]);
	if (!is_builtin(cmd) && throw_error(cmd->argument[0], cmdpath))
		return ;
	env_cast();
	g_gb.last_fd = fork();
	if (!g_gb.last_fd)
		child_proc(cmdpath, cmd, pip, p);
	close_io(cmd);
	signal(SIGINT, SIG_IGN);
	free(cmdpath);
}
