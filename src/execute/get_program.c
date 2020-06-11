/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_program.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 22:22:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 21:18:34 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_program(char **args, int *types)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (types[i] == PIPEDCOMMAND || types[i] == COMMAND)
			return (args[i]);
		i++;
	}
	return (NULL);
}
