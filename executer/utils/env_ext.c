/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:37:15 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/23 08:02:51 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_envval(char *env_var)
{
	t_envl	*node;

	node = g_gb.env;
	while (node)
	{
		if (!ft_strcmp(node->key, env_var))
			return (node->value);
		node = node->next;
	}
	return ("none");
}

void	set_envval(char *key, char *new_val)
{
	t_envl	*node;

	node = g_gb.env;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
		{
			free(node->value);
			node->value = new_val;
			return ;
		}
		node = node->next;
	}
}

t_envl	*get_env(char *env_var)
{
	t_envl	*node;

	node = g_gb.env;
	while (node)
	{
		if (!ft_strcmp(node->key, env_var))
			return (node);
		node = node->next;
	}
	return (NULL);
}
