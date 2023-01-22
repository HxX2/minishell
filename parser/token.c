/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:58:32 by aamoussa          #+#    #+#             */
/*   Updated: 2022/11/03 06:55:09 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// skip spaces and return true in case of finding the given token
int	skip_and_find(char **ps, char *es, char *tok)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	return (*s && ft_strchr(tok, *s));
}

// check if there is append rederiction or heredoc and set token type
void	get_token_helper(char **s, int *ret)
{
	char	*tmp;

	tmp = *s;
	if (*ret == '<')
	{	
		if (*(tmp + 1) == '<')
		{	
			*ret = '-';
			tmp++;
		}
	}
	if (*ret == '>')
	{	
		if (*(tmp + 1) == '>')
		{	
			*ret = '+';
			tmp++;
		}
	}
	*s = tmp;
}

void	helper(char **pt, char **s)
{
	if (pt)
		*pt = *s;
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	helper(q, &s);
	ret = *s;
	if (s < es)
	{
		if (ft_strchr(SYMBOLE, *s))
			ret = *(ft_strchr(SYMBOLE, *s));
		if (!ft_strchr(SYMBOLE, *s))
			ret = 'a';
		get_token_helper(&s, &ret);
		s++;
		while (s < es && ret == 'a' && !ft_strchr(WHITESPACE, *s)
			&& !ft_strchr(SYMBOLE, *s))
			s++;
		helper(eq, &s);
		while (s < es && ft_strchr(WHITESPACE, *s))
			s++;
		*ps = s;
	}
	return (ret);
}
