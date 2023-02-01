/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:07:37 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/27 18:43:09 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	protect_signals(int end[2], char *line)
{
	if (g_gb.here_doc == 1)
	{
		close(end[1]);
		close(end[0]);
		return (-1);
	}
	if (!line)
	{
		close(end[1]);
		return (end[0]);
	}
	return (0);
}

int	sig_and_firstline(int *end, char *lim, bool flag)
{
	char	*line;
	char	*newline;
	int		fd;

	while (1)
	{	
		line = readline("< ");
		fd = protect_signals(end, line);
		if (fd != 0)
			return (fd);
		if (*line && ft_strcmp(lim, line))
			here_doc_expand(&line, flag);
		if (!ft_strcmp(lim, line))
			break ;
		newline = ft_strjoin(line, "\n");
		write(end[1], newline, ft_strlen(newline));
		free(newline);
		ft_free(&line);
	}
	free(line);
	close(end[1]);
	return (end[0]);
}

int	here_doc(char *lim, bool flag)
{
	int		end[2];
	int		fd;

	if (g_gb.here_doc == 1)
		return (-1);
	g_gb.input = dup(0);
	signal(SIGINT, sig_handl);
	pipe(end);
	fd = get_first_line(end, lim, flag);
	if (fd == 0)
	{	
		close(end[1]);
		return (end[0]);
	}
	else if (fd > 1)
		return (fd);
	return (sig_and_firstline(end, lim, flag));
}
