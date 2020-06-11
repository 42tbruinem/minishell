/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 22:22:24 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 20:37:42 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void		ft_str2print(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		ft_printf("%s%c", str[i], (str[i + 1]) ? ' ' : '\n');
		i++;
	}
}

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
	if (!str)
		return (-1);
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
		return (0);
	entries = ft_split(path, ':');
	if (!entries)
		return (0);
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

int		run_program(t_msh *prog, t_cmd *cmd, char *abspath)
{
	int pid;

	if (!prog->envp)
		return (1);
	pid = fork();
	if (!pid)
	{
		close_ifnot(&prog->file_arr, cmd->iostream);
		if (cmd->iostream[READ] != -1 &&
			dup2(cmd->iostream[READ], STDIN) == -1)
			exit(0);
		if (cmd->iostream[WRITE] != -1 &&
			dup2(cmd->iostream[WRITE], STDOUT) == -1)
			exit(0);
		if (abspath && execve(abspath, cmd->args, prog->envp) == -1)
			exit(0);
		if (!abspath && execve(cmd->args[0], cmd->args, prog->envp) == -1)
			exit(0);
		close_iostream(cmd->iostream);
		exit(0);
	}
	vec_add(&g_pid, &pid);
	close_iostream(cmd->iostream);
	free(abspath);
	return (0);
}

int		run_builtin(t_msh *prog, t_cmd *cmd, int id)
{
	int						pid;
	static const t_builtin	builtins[] = {
	[B_ENV] = &ft_env,
	[B_PWD] = &ft_pwd,
	[B_ECHO] = &ft_echo,
	[B_EXPORT] = &ft_export,
	[B_UNSET] = &ft_unset,
	[B_EXIT] = &ft_exit,
	[B_CD] = &ft_cd
	};

	if (cmd->iostream[READ] == -1 && cmd->iostream[WRITE] == -1)
	{
		builtins[id](prog, ft_str2len(cmd->args), cmd->args);
		return (0);
	}
	pid = fork();
	if (!pid)
	{
		close_ifnot(&prog->file_arr, cmd->iostream);
		if (cmd->iostream[READ] != -1 &&
			dup2(cmd->iostream[READ], STDIN) == -1)
			exit(0);
		if (cmd->iostream[WRITE] != -1 &&
			dup2(cmd->iostream[WRITE], STDOUT) == -1)
			exit(0);
		builtins[id](prog, ft_str2len(cmd->args), cmd->args);
		close_iostream(cmd->iostream);
		exit(0);
	}
	vec_add(&g_pid, &pid);
	close_iostream(cmd->iostream);
	return (0);
}

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

int		execute(t_msh *prog, t_cmd *cmd)
{
	char	*abspath;
	int		builtin;

	abspath = NULL;
	builtin = is_builtin(cmd->args[0]);
	if (builtin >= 0)
		return (run_builtin(prog, cmd, builtin));
	is_executable(cmd->args[0], &abspath, prog->env);
	return (run_program(prog, cmd, abspath));
}
