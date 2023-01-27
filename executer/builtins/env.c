/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:24:32 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/26 18:50:58 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

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
