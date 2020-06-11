/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 23:02:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 21:00:37 by tbruinem      ########   odam.nl         */
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

static	char	*get_cwd(void)
{
	char	*path;
	char	*res;
	size_t	size;

	size = 20;
	path = malloc(sizeof(char) * (size + 1));
	res = getcwd(path, size + 1);
	while (!res && errno == ERANGE)
	{
		size += 20;
		free(path);
		path = malloc(sizeof(char) * (size + 1));
		if (!path)
			return (NULL);
		res = getcwd(path, size + 1);
	}
	return (path);
}

void			ft_cd(t_msh *prog, int argc, char **argv)
{
	char	*path;
	char	*newpwd;

	if (argc <= 1 || argc > 3)
		return ;
	path = ft_strdup(argv[1]);
	if (!path)
		return ;
	if (chdir(path) == -1)
	{
		free(path);
		return (perror(strerror(errno)));
	}
	env_val_set("OLDPWD", prog->env, env_val_get("PWD", prog->env));
	newpwd = get_cwd();
	env_val_set("PWD", prog->env, newpwd);
	env_update(prog);
	free(newpwd);
	free(path);
}
