/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:51:04 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/22 15:07:48 by zlafou           ###   ########.fr       */
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

void	ft_chdir(char *path)
{
	if (chdir(path) < 0)
	{
		g_gb.exit_statut = 1;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		if (!is_file(path))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": Not a directory\n", 2);
	}
	else
	{
		set_envval("OLDPWD", get_envval("PWD"));
		set_envval("PWD", getcwd(NULL, 0));
		free(g_gb.curent);
		if (get_env("PWD"))
			g_gb.curent = ft_strdup(get_envval("PWD"));
		printf("%s\n", getcwd(NULL, 0));
	}
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
