/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 09:36:31 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/28 19:11:23 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

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

void	child_proc(char *cmdpath, t_execcmd *cmd, int in, int out)
{
	if (cmd->input > 0)
	{
		dup2(cmd->input, 0);
		close(cmd->input);
	}
	else if (in != -1)
	{
		dup2(in, 0);
		close(in);
	}
	if (cmd->output > 1)
	{
		dup2(cmd->output, 1);
		close(cmd->output);
	}
	else if (out != -1)
	{
		dup2(out, 1);
		close(out);
	}
	execve(cmdpath, cmd->argument, g_gb.envp);
}

void	exe_cmd(t_execcmd *cmd, int in, int out)
{
	char	*cmdpath;
	int		ch_status;
	pid_t	pid;

	cmdpath = get_cmd_path(cmd->argument[0]);
	if (throw_error(cmd->argument[0], cmdpath))
		return ;
	env_cast();
	pid = fork();
	if (!pid)
		child_proc(cmdpath, cmd, in, out);
	close(in);
	close(out);
	if (cmd->input > 0)
		close(cmd->input);
	if (cmd->output > 1)
		close(cmd->output);
	while (wait(&ch_status) != -1)
		;
	g_gb.exit_statut = WEXITSTATUS(ch_status);
}
