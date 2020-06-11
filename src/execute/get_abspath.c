/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_abspath.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 21:33:20 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 21:33:21 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static	int	is_abspath(char **abspath, char *entry, char *program)
{
	char		*tmp;
	struct stat	unused;

	tmp = ft_str3join(entry, "/", program);
	if (stat(tmp, &unused) != -1)
	{
		*abspath = tmp;
		return (1);
	}
	free(tmp);
	return (0);
}

void	get_abspath(char *program, char **abspath_to_exe, t_var *env)
{
	char		*path;
	char		**entries;
	size_t		i;

	i = 0;
	path = env_val_get("PATH", env);
	if (!path)
		exit(0);
	entries = ft_split(path, ':');
	if (!entries)
		exit(0);
	while (entries[i])
	{
		if (is_abspath(abspath_to_exe, entries[i], program))
			break ;
		i++;
	}
	ft_str2clear(entries);
}
