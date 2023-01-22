/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:10:21 by zlafou            #+#    #+#             */
/*   Updated: 2023/01/19 06:41:57 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_xalloc(size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (!ptr)
		return (0);
	while (n)
		((unsigned char *)ptr)[--n] = 0;
	return (ptr);
}

void	ft_rwipe(void *ptr, int plvl)
{
	int		i;
	int		b;
	void	**p;

	p = (void **)ptr;
	b = 1;
	if (plvl < 0)
	{
		plvl *= -1;
		b = 0;
	}
	if (plvl > 1)
	{
		i = 0;
		while (p && p[i])
		{
			if (plvl > 2)
				ft_rwipe((void **)p[i], -1 * (plvl - 1));
			free(p[i]);
			i++;
		}
	}
	if (b)
		free(p);
}
