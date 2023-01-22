/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:24:32 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/22 09:40:15 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env(void)
{
	t_envl	*node;

	node = g_gb.env;
	while (node)
	{
		if (node->value)
			printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	g_gb.exit_statut = 0;
}
