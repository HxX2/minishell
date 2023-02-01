/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 05:44:09 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/29 20:16:53 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h"

int	skip_par(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '-')
			j++;
		while (args[i][j] == 'n' )
			j++;
		if (args[i][j])
			break ;
		i++;
	}
	return (i);
}

void	echo(char **args)
{
	int	i;
	int	p;

	i = skip_par(args);
	p = (i < 2);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (p)
		printf("\n");
	g_gb.exit_statut = 0;
}
