/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:11:34 by zlafou            #+#    #+#             */
/*   Updated: 2023/02/01 18:34:31 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executer/executer.h"

int	get_buffer(char **buffer)
{
	char	*pr;

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
		if (is_builtin(x_cmd))
			exec_builtins (x_cmd);
		else
			n_pipe(cmd, -1, -1, NULL);
	}
	else
		n_pipe(cmd, -1, -1, NULL);
	waitproc();
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
