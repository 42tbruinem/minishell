/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 23:02:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/30 12:46:50 by rlucas        ########   odam.nl         */
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

extern int errno;

char	*get_cwd(void)
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

void	ft_export(int argc, char **argv, t_var **env)
{
	size_t	i;
	size_t	tmp;

	if (argc == 1)
		return ;
	i = 1;
	while (argv[i])
	{
		tmp = ft_strclen(argv[i], '=');
		argv[i][tmp] = '\0';
		if (tmp != ft_strlen(argv[i]))
			(void)env_val_set(argv[i], *env, &argv[i][tmp + 1]);
		i++;
	}
}

void	ft_exit(int argc, char **argv, t_var **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	std_exit(NULL); //euhm, yea..
}

void	ft_unset(int argc, char **argv, t_var **env)
{
	size_t	i;

	if (argc == 1)
		return ;
	i = 1;
	while (argv[i])
	{
		env_unset(env, argv[i]);
		i++;
	}
}

void	ft_echo(int argc, char **argv, t_var **env)
{
	int	i;

	i = 1;
	(void)env;
	while (argc >= 2 && argv[i])
	{
		if (i != 1 || ft_strncmp(argv[1], "-n", 2) != 0)
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (i + 1 < argc)
				write(1, " ", 1);
		}
		i++;
	}
	if (argc == 1 || ft_strncmp(argv[1], "-n", 2) != 0)
		write(1, "\n", 1);
}

void	ft_env(int argc, char **argv, t_var **env)
{
	if (argc != 1 || !argv)
		return ;
	env_print(*env);
}

void	ft_pwd(int argc, char **argv, t_var **env)
{
	char	*path;
	char	*res;
	size_t	size;

	(void)argc;
	(void)argv;
	(void)env;
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
		ft_printf("%s", path);
	free(path);
}

void	ft_cd(int argc, char **argv, t_var **env)
{
	char	*path;

	if (argc <= 1 || argc > 3)
		return ;
//	if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
//		path = ft_strdup(env_val_get(&env, "OLDPWD"));
//	else if (argc == 3)
//	{
//		path = ft_strdup(get_envvar_value(&env, "PWD"));
//		path = ft_strreplace(path, argv[1], argv[2]);
//	}
//	else
	path = ft_strdup(argv[1]);
	if (!path)
		return ;
	if (chdir(path) == -1)
	{
		free(path);
		return (perror(strerror(errno)));
	}
	env_val_set("OLDPWD", *env, env_val_get("PWD", *env));
	env_val_set("PWD", *env, get_cwd());
	free(path);
}
