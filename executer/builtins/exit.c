/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:31:58 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/26 18:51:07 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

static void	throw_err(char *ecode)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(ecode, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static int	is_valid_ecode(char *ecode)
{
	int	i;

	i = 0;
	if (ecode[i] == '-' || ecode[i] == '+')
		i++;
	while (ecode[i])
	{
		if (!ft_isdigit(ecode[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	printf("exit\n");
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit(1);
	}
	if (args[1])
	{
		if (!is_valid_ecode(args[1]))
			throw_err(args[1]);
		else
			exit(ft_atoi(args[1]));
	}
	else
		exit(0);
}

/**
 * @brief error handler for exit cmd
 * 
 * @e minishell: exit: too many arguments
 * @return 1
 * 
 * @e minishell: exit: dgdsgsdg: numeric argument required
 * @return 255
 */