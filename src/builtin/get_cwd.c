/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 13:51:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/18 13:53:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <msh_builtin.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

char			*get_cwd(void)
{
	char	*path;
	char	*res;
	size_t	size;

	size = 20;
	path = malloc(sizeof(char) * (size + 1));
	if (!path)
		exit(1);
	res = getcwd(path, size + 1);
	while (!res && errno == ERANGE)
	{
		size += 20;
		free(path);
		path = malloc(sizeof(char) * (size + 1));
		if (!path)
			exit(1);
		res = getcwd(path, size + 1);
	}
	return (path);
}
