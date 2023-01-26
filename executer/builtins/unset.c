/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:07:41 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/26 18:51:29 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

int	is_valid_id(char *id)
{
	int	i;

	i = 0;
	while (id[i])
	{
		if (!ft_isalpha(id[i]) && id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	throw_err(char *id)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(id, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_gb.exit_statut = 1;
}

void	remove_id(char *id)
{
	t_envl	*node;
	t_envl	*prv;

	node = g_gb.env;
	prv = NULL;
	while (node)
	{
		if (!ft_strcmp(id, node->key))
		{
			if (prv == NULL)
				g_gb.env = node->next;
			else
				prv->next = node->next;
			free(node->key);
			free(node->value);
			free(node);
			return ;
		}
		prv = node;
		node = node->next;
	}
}

void	unset(char **args)
{
	int	i;

	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		if (!is_valid_id(args[i]))
			throw_err(args[i]);
		else
			remove_id(args[i]);
		i++;
	}
	g_gb.exit_statut = 0;
}
