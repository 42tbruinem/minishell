/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 22:22:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/29 23:00:48 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	char	*path;
	char	**entries;
	char	*tmp;
	size_t	i;

	i = 0;
	path = env_val_get("PATH", env);
	if (!path)
		return (0); //error
	entries = ft_split(path, ':');
	if (!entries)
		return (0); //error
	while (entries[i])
	{
		tmp = ft_str3join(entries[i], "/", *abspath_to_exe);
		if (stat(tmp, NULL) != -1)
		{
			*abspath_to_exe = tmp;
			return (1);
		}
		free(tmp);
	}
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
	builtins[id](ft_str2len(args), args, env);
}

int		execute(char **args, t_var *env)
{
	char	*name;
	char	*abspath;
	char	**envp;
	int		builtin;

	abspath = NULL;
	name = ft_strdup(*args);
	if (!name)
		return (1); //error
	if (is_executable(args[0], &abspath, env))
		return (run_program(abspath, args, env));
	builtin = is_builtin(args[0]);
	if (builtin < 0)
		return (1); //error (not an executable or a builtin)



}