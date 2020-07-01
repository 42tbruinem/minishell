/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_abspath.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 21:33:20 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/07/01 12:57:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <msh_env.h>
#include <msh_exec.h>
#include <msh_builtin.h>

static int		is_abspath(char **abspath, char *entry, char *program)
{
	char		*tmp;
	struct stat	unused;

	tmp = ft_str3join(entry, "/", program);
	if (!tmp)
		exit(1);
	if (stat(tmp, &unused) != -1)
	{
		*abspath = tmp;
		return (1);
	}
	free(tmp);
	return (0);
}

static int		check_if_path(char *program, char **abspath)
{
	struct stat	unused;

	if (stat(program, &unused) != -1)
	{
		*abspath = ft_strdup(program);
		if (!*abspath)
			exit(1);
		return (1);
	}
	return (0);
}

static void		command_not_found(char *program)
{
	ft_printf_fd(STDERR, "%s: command not found\n", program);
	return ;
}

static void		check_envpath(char *program, char **abspath_to_exe, t_var *env)
{
	char	*path;
	char	**entries;
	size_t	i;

	i = 0;
	path = env_val_get("PATH", env, 4);
	if (!path)
		return (command_not_found(program));
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
}

void			get_abspath(char *program, char **abspath_to_exe, t_var *env)
{
	if (!ft_strchr(program, '/'))
		check_envpath(program, abspath_to_exe, env);
	if (!*abspath_to_exe)
		check_if_path(program, abspath_to_exe);
	if (ft_strlen(program) == 0 || *abspath_to_exe == NULL)
		return (command_not_found(program));
}
