/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 22:22:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/29 23:53:26 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t		ft_str2len(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	ft_str2cmpstr(const char **str2, char *str)
{
	long long	i;

	i = 0;
	while (str2[i])
	{
		if (ft_strcmp((char *)str2[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

long long	is_builtin(char *program)
{
	static const char	*builtins[] = {
	[B_CD] = "cd",
	[B_ECHO] = "echo",
	[B_PWD] = "pwd",
	[B_EXPORT] = "export",
	[B_UNSET] = "unset",
	[B_ENV] = "env",
	[B_EXIT] = "exit",
	[7] = NULL,
	};

	return (ft_str2cmpstr(builtins, program));
}

int		is_executable(char *program, char **abspath_to_exe, t_var *env)
{
	char		*path;
	char		**entries;
	char		*tmp;
	struct stat	unused;
	size_t		i;

	i = 0;
	path = env_val_get("PATH", env);
	if (!path)
		return (0); //error
	entries = ft_split(path, ':');
	if (!entries)
		return (0); //error
	while (entries[i])
	{
		tmp = ft_str3join(entries[i], "/", program);
		if (stat(tmp, &unused) != -1)
		{
			*abspath_to_exe = tmp;
			ft_str2clear(entries);
			return (1);
		}
		i++;
		free(tmp);
	}
	ft_str2clear(entries);
	return (0);
}

int		run_program(char *abspath, char **args, t_var *env)
{
	char **envp;

	envp = env_convert(env);
	if (!envp)
		return (1); //error
	if (!fork())
		if (execve(abspath, args, envp) == -1)
			return (1); //error
	(void)ft_str2clear(envp);
	free(abspath);
	(void)ft_str2clear(args);
	return (0);
}

int		run_builtin(char **args, t_var *env, int id)
{
	static const t_builtin builtins[] = {
	[B_ENV] = &ft_env,
	[B_PWD] = &ft_pwd,
	[B_ECHO] = &ft_echo,
	[B_EXPORT] = &ft_export,
	[B_UNSET] = &ft_unset,
	[B_EXIT] = &ft_exit,
	[B_CD] = &ft_cd};

//	printf("Executing builtin!\n");
	builtins[id](ft_str2len(args), args, &env);
	return (0);
}

int		execute(char **args, t_var *env)
{
	char	*abspath;
	int		builtin;

	abspath = NULL;
	if (is_executable(args[0], &abspath, env))
		return (run_program(abspath, args, env));
	builtin = is_builtin(args[0]);
	if (builtin < 0)
		return (1); //error (not an executable or a builtin)
	return (run_builtin(args, env, builtin));
}
