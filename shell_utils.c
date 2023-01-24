/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:14:32 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/24 13:44:57 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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

void	free_all(t_cmd *cmd)
{
	t_pipecmd	*pipcmd;
	t_execcmd	*execcmd;
	int			i;

	i = 0;
	if (cmd->type == PIPE)
	{
		pipcmd = (t_pipecmd *)(cmd);
		free_all(pipcmd->left);
		free_all(pipcmd->right);
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

void	free_cmd(t_cmd *cmd)
{
	free_all(cmd);
}
