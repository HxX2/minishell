/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:21:11 by zlafou            #+#    #+#             */
/*   Updated: 2023/02/03 21:17:16 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	n_pipe(t_cmd *cmd, int in, int out, int *p)
{
	t_execcmd	*exec;
	t_pipecmd	*pip;
	int			std[2];

	std[0] = -1;
	std[1] = -1;
	if (cmd->type == EXEC)
	{
		exec = (t_execcmd *)cmd;
		exe_cmd(exec, in, out, p);
		close(in);
		close(out);
	}
	if (cmd->type == PIPE)
	{
		pipe(std);
		pip = (t_pipecmd *)cmd;
		pip->std = std;
		n_pipe(pip->left, in, pip->std[1], pip->std);
		n_pipe(pip->right, pip->std[0], -1, pip->std);
		close(in);
		close(out);
		close(std[0]);
		close(std[1]);
	}
}

void	exec_builtins(t_execcmd *x_cmd)
{
	int	std_in;
	int	std_out;

	std_in = dup(0);
	std_out = dup(1);
	dup_red_pipe(x_cmd, -1, -1);
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
	dup2(std_in, 0);
	dup2(std_out, 1);
	close(std_in);
	close(std_out);
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
	close(out);
	close(in);
}

void	close_io(t_execcmd *cmd)
{
	if (cmd->input > 0)
		close(cmd->input);
	if (cmd->output > 1)
		close(cmd->output);
}

void	waitproc(void)
{
	int	ch_status;
	int	ret_val;

	ret_val = 1;
	while (ret_val != -1)
	{
		ret_val = wait(&ch_status);
		if (ret_val == g_gb.last_fd)
		{
			if (WIFEXITED(ch_status))
				g_gb.exit_statut = WEXITSTATUS(ch_status);
			else
			{
				g_gb.exit_statut = 128 + WTERMSIG(ch_status);
			}
		}
	}
	signals();
}
