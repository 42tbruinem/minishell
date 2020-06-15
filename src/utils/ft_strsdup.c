/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 13:54:20 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/15 13:55:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

size_t	ft_strslen(char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_strchr(set, str[i]) == 0)
		i++;
	return (i);
}

char	*ft_strsdup(char *str, char *set)
{
	size_t	len;
	size_t	i;
	char	*new;

	i = 0;
	len = ft_strslen(str, set);
	new = ft_calloc(sizeof(char), (len + 1));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = str[i];
		if (!new)
			return (NULL);
		i++;
	}
	new[i] = 0;
	return (new);
}
