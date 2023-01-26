/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:09:17 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/26 18:36:16 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_arg(t_list **head, char **q, char **eq)
{
	size_t	len;
	char	*str;

	len = (*eq - *q);
	str = ft_substr(*q, 0, len);
	ft_lstadd_back(head, ft_lstnew(str, NOTHING));
}

void	raise_error(char *message, int exitcode, int tok, t_cmd *cmd)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd(tok, 2);
	ft_putstr_fd("\n", 2);
	if (cmd)
		free_cmd(cmd);
	g_gb.exit_statut = exitcode;
	g_gb.status = 1;
}

int	skip_and_find_0(char **ps, char *es)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	return (!*s);
}
