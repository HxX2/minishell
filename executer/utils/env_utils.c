/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:13:22 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/27 20:38:38 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

int	envp_size(void)
{
	t_envl	*tmp;
	int		i;

	i = 0;
	tmp = g_gb.env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_envl	*new_envp(char *env_var)
{
	t_envl	*node;
	char	*sp;

	node = (t_envl *)malloc(sizeof(t_envl));
	sp = ft_strchr(env_var, '=');
	if (sp)
	{
		*sp = '\0';
		node->key = ft_strdup(env_var);
		node->value = ft_strdup(sp + 1);
		*sp = '=';
	}
	else
	{
		node->key = ft_strdup(env_var);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

void	env_push(t_envl **lst, t_envl *new)
{
	t_envl	*tmp;

	tmp = *lst;
	if (!(*lst))
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{	
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	env_cast(void)
{
	int		i;
	t_envl	*node;
	char	*jstr1;
	char	*jstr2;

	ft_rwipe(g_gb.envp, 2);
	g_gb.envp = (char **)ft_xalloc(sizeof(char *) * (envp_size() + 1));
	i = 0;
	node = g_gb.env;
	while (node)
	{
		jstr1 = ft_strjoin(node->key, "=");
		jstr2 = ft_strjoin(jstr1, node->value);
		free(jstr1);
		if (!jstr2)
		{
			node = node->next;
			continue ;
		}
		g_gb.envp[i++] = jstr2;
		node = node->next;
	}
}

void	set_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		env_push(&g_gb.env, new_envp(envp[i++]));
}
