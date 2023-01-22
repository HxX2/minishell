/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 09:36:31 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/22 17:14:35 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_paths(char *path)
{
	char **paths;

	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

char	*get_cmd_path(char *cmd)
{
	char 	**paths;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (cmd);
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
				return(path);
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

void child_proc(char *cmdpath, char **args, char **envp)
{
	execve(cmdpath, args, envp);
}

void	exe_cmd(char **args)
{
	char	*cmdpath;
	pid_t	pid;

	cmdpath = get_cmd_path(args[0]);
	if (throw_error(args[0], cmdpath))
		return ;
	pid = fork();
	env_cast();
	if (!pid)
		child_proc(cmdpath, args, g_gb.envp);
	while (wait(NULL) != -1)
		;
}