/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_strclen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:53:42 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 16:53:51 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

size_t		env_strclen(char *line, const char *chars)
{
	size_t		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			if (!line[i + 1])
				return (i + 1);
			i += 2;
			continue;
		}
		if (ft_strchr(chars, line[i]))
			return (i);
		i++;
	}
	return (i);
}
