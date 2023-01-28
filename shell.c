/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:11:34 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/28 19:22:56 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executer/executer.h"

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

int	get_buffer(char **buffer)
{
	char *pr;

	ft_free(buffer);
	pr = ps1();
	*buffer = readline(pr);
	free(pr);
	g_gb.here_doc = 0;
	if (!*buffer)
		return (0);
	if (!*buffer[0])
		return (1);
	return (2);
}

void	freee(t_cmd **cmd)
{
	if (*cmd)
	{
		free_cmd(*cmd);
		*cmd = NULL;
	}
}

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

void	executer_sudo(t_cmd *cmd)
{
	t_execcmd	*x_cmd;

	env_cast();
	if (cmd->type == EXEC)
	{
		x_cmd = (t_execcmd *)cmd;
		if (!x_cmd->argument)
		{
			if (x_cmd->input > 0)
				close(x_cmd->input);
			if (x_cmd->output > 1)
				close(x_cmd->output);
			return ;
		}
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
		else
			n_pipe(cmd, -1, -1);
	}
	else
		n_pipe(cmd, -1, -1);
}

void	leave(void)
{
	printf("exit\n");
	exit(g_gb.exit_statut);
}

void	parser_sudo(char **envp)
{
	char	*buff_s;
	char	*buff_e;
	t_cmd	*cmd;
	char	*buffer;
	int		i;

	cmd = NULL;
	buffer = NULL;
	while (42)
	{
		g_gb.status = 0;
		i = get_buffer(&buffer);
		if (i == 0)
			leave();
		else if (i == 1)
			continue ;
		buff_e = &buffer[ft_strlen(buffer)];
		add_history(buffer);
		buff_s = buffer;
		freee(&cmd);
		cmd = parser(&buff_s, buff_e, envp);
		if (!cmd)
			continue ;
		executer_sudo(cmd);
	}
}

int	main(int ac, char **av, char **ep)
{
	(void)ac;
	(void)av;
	g_gb.output = 1;
	set_envp(ep);
	g_gb.curent = ft_strdup(get_envval("PWD"));
	signals();
	parser_sudo(ep);
	return (g_gb.exit_statut);
}
