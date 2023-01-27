/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 03:11:57 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/26 18:51:15 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static void	print_env(void)
{
	t_envl	*node;

	node = g_gb.env;
	while (node)
	{
		if (!node->value)
			printf("declare -x %s\n", node->key);
		else
			printf("declare -x %s=\"%s\"\n", node->key, node->value);
		node = node->next;
	}
	g_gb.exit_statut = 0;
}

static void	throw_err(char *id, t_envl *node)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(id, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(node->key);
	free(node->value);
	free(node);
	g_gb.exit_statut = 1;
}

static void	env_amend(t_envl *evar)
{
	t_envl	*tmp;

	if (!get_env(evar->key))
		env_push(&g_gb.env, evar);
	else if (evar->value)
	{
		tmp = get_env(evar->key);
		free(tmp->value);
		tmp->value = evar->value;
		free(evar->key);
		free(evar);
	}
}

void	export(char **args)
{
	int		i;
	t_envl	*node;

	if (!args[1])
		print_env();
	i = 1;
	while (args[i])
	{
		node = new_envp(args[i]);
		if (!is_valid_id(node->key))
			throw_err(args[i], node);
		else
			env_amend(node);
		i++;
	}
	g_gb.exit_statut = 0;
}
