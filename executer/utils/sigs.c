/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:22:15 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/26 18:52:07 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

void	sig_int(int signal)
{
	if (signal == SIGINT)
	{
		g_gb.exit_statut = 1;
		char *s = ps1();
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