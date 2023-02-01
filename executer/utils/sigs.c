/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:22:15 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/29 20:16:17 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	sig_int(int signal)
{
	char	*s;

	if (signal == SIGINT)
	{
		s = ps1();
		g_gb.exit_statut = 1;
		printf("\33[2K\r> %s\n%s", rl_line_buffer, s);
		rl_replace_line("", 0);
		free(s);
	}
}

void	signals(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}

void	ch_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
