/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:14:32 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/29 20:20:24 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include "executer/executer.h"

void	free_args_list(t_list **args)
{
	t_list	*arg;

	while ((*args))
	{
		ft_free(&((*args)->content));
		arg = (*args);
		(*args) = (*args)->next;
		free(arg);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_pipecmd	*pipcmd;
	t_execcmd	*execcmd;
	int			i;

	i = 0;
	if (cmd->type == PIPE)
	{
		pipcmd = (t_pipecmd *)(cmd);
		free_cmd(pipcmd->left);
		free_cmd(pipcmd->right);
		free(pipcmd);
	}
	else if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)(cmd);
		while (execcmd->argument && execcmd->argument[i])
			ft_free(&execcmd->argument[i++]);
		free_args_list(&(execcmd->args));
		free(execcmd->argument);
		free(execcmd);
	}
}

int	is_builtin(t_execcmd *x_cmd)
{
	if (!ft_strcmp(x_cmd->argument[0], "env"))
		return (1);
	else if (!ft_strcmp(x_cmd->argument[0], "unset"))
		return (1);
	else if (!ft_strcmp(x_cmd->argument[0], "pwd"))
		return (1);
	else if (!ft_strcmp(x_cmd->argument[0], "exit"))
		return (1);
	else if (!ft_strcmp(x_cmd->argument[0], "cd"))
		return (1);
	else if (!ft_strcmp(x_cmd->argument[0], "export"))
		return (1);
	else if (!ft_strcmp(x_cmd->argument[0], "echo"))
		return (1);
	return (0);
}

char	*ps1(void)
{
	char	*sj1;
	char	*sj2;
	char	*sj3;
	char	*sj4;

	sj1 = ft_strjoin(BLUE, get_envval("USER"));
	sj2 = ft_strjoin(sj1, RESET "@" BLUE "minishell " RESET "[" PURPLE);
	sj3 = ft_strjoin(sj2, get_envval("PWD"));
	sj4 = ft_strjoin(sj3, RESET "] \n> ");
	free(sj1);
	free(sj2);
	free(sj3);
	return (sj4);
}

void	leave(void)
{
	printf("exit\n");
	exit(g_gb.exit_statut);
}
