/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 23:02:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:03:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <msh_builtin.h>

void	ft_pwd(t_msh *prog, int argc, char **argv)
{
	char	*path;
	char	*res;
	size_t	size;

	(void)argc;
	(void)argv;
	(void)prog;
	size = 20;
	path = malloc(sizeof(char) * (size + 1));
	res = getcwd(path, size + 1);
	while (!res && errno == ERANGE)
	{
		size += 20;
		free(path);
		path = malloc(sizeof(char) * (size + 1));
		if (!path)
			return ;
		res = getcwd(path, size + 1);
	}
	if (res)
		ft_printf("%s\n", path);
	free(path);
}
