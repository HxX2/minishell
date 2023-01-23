/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:51:04 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/23 08:13:42 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_file(char	*path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (1);
	return (S_ISREG(sb.st_mode));
}

void	update_dir(void)
{
	char	*oldpwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		oldpwd = ft_strdup(get_envval("PWD"));
		set_envval("OLDPWD", oldpwd);
		set_envval("PWD", ft_strjoin(g_gb.curent, "/."));
		pwd = g_gb.curent;
		g_gb.curent = ft_strjoin(g_gb.curent, "/.");
		free(pwd);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	else
	{
		oldpwd = ft_strdup(get_envval("PWD"));
		set_envval("OLDPWD", oldpwd);
		set_envval("PWD", pwd);
		free(g_gb.curent);
		g_gb.curent = ft_strdup(pwd);
		printf("%s\n", pwd);
	}
}

void	ft_chdir(char *path)
{
	if (chdir(path) < 0)
	{
		g_gb.exit_statut = 1;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		if (access(path, F_OK))
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (is_file(path))
			ft_putstr_fd(": Not a directory\n", 2);
	}
	else
		update_dir();
}

void	cd(char **args)
{
	char	*evar;

	evar = get_envval("HOME");
	if (!args[1])
	{
		if (!ft_strcmp(evar, "none"))
		{
			g_gb.exit_statut = 1;
			ft_putstr_fd("minishell: cd : HOME not set\n", 2);
		}
		else
			ft_chdir(get_envval("HOME"));
	}
	else
		ft_chdir(args[1]);
}
