/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_abspath.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 21:33:20 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/24 14:58:35 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <msh_env.h>
#include <msh_exec.h>

static int	is_abspath(char **abspath, char *entry, char *program)
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

static int	check_if_path(char *program, char **abspath)
{
	struct stat	unused;

	if (stat(program, &unused) != -1)
	{
		*abspath = ft_strdup(program);
		return (1);
	}
	return (0);
}

void		get_abspath(char *program, char **abspath_to_exe, t_var *env)
{
	char		*path;
	char		**entries;
	size_t		i;

	i = 0;
	if (check_if_path(program, abspath_to_exe))
		return ;
	path = env_val_get("PATH", env, 4);
	if (!path)
		exit(1);
	entries = ft_split(path, ':');
	if (!entries)
		exit(1);
	while (entries[i])
	{
		if (is_abspath(abspath_to_exe, entries[i], program))
			break ;
		i++;
	}
	ft_str2clear(entries);
	if (*abspath_to_exe == NULL)
		ft_printf_fd(STDERR, "%s: command not found\n", program);
}
