/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:21:11 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/29 20:26:57 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	n_pipe(t_cmd *cmd, int in, int out)
{
	t_execcmd	*exec;
	t_pipecmd	*pip;
	int			std[2];

	if (cmd->type == EXEC)
	{
		exec = (t_execcmd *)cmd;
		exe_cmd(exec, in, out);
	}
	if (cmd->type == PIPE)
	{
		pipe(std);
		pip = (t_pipecmd *)cmd;
		pip->std = std;
		n_pipe(pip->left, in, pip->std[1]);
		n_pipe(pip->right, pip->std[0], -1);
	}
}

void	exec_builtins(t_execcmd *x_cmd)
{
	if (!ft_strcmp(x_cmd->argument[0], "env"))
		env();
	else if (!ft_strcmp(x_cmd->argument[0], "unset"))
		unset(x_cmd->argument);
	else if (!ft_strcmp(x_cmd->argument[0], "pwd"))
		pwd();
	else if (!ft_strcmp(x_cmd->argument[0], "exit"))
		ft_exit(x_cmd->argument);
	else if (!ft_strcmp(x_cmd->argument[0], "cd"))
		cd(x_cmd->argument);
	else if (!ft_strcmp(x_cmd->argument[0], "export"))
		export(x_cmd->argument);
	else if (!ft_strcmp(x_cmd->argument[0], "echo"))
		echo(x_cmd->argument);
}

void	dup_red_pipe(t_execcmd *cmd, int in, int out)
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
}
