/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 23:02:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/18 13:51:05 by tbruinem      ########   odam.nl         */
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
#include <msh_env.h>

static void		cd_home(t_msh *prog)
{
	char	*home;

	home = env_val_get("HOME", prog->env);
	if (!home)
	{
		ft_printf_fd(2, "msh: cd: HOME not set\n");
		return ;
	}
	if (chdir(home) == -1)
	{
		free(home);
		ft_printf_fd(2, "msh: %s\n", strerror(errno));
		return ;
	}
	env_val_set("OLDPWD", &prog->env, env_val_get("PWD", prog->env));
	env_val_set("PWD", &prog->env, home);
	env_update(prog);
}

void			ft_cd(t_msh *prog, int argc, char **argv)
{
	char	*path;
	char	*newpwd;

	if (argc == 1)
		return (cd_home(prog));
	path = ft_strdup(argv[1]);
	if (!path)
		exit(1);
	if (chdir(path) == -1)
	{
		free(path);
		ft_printf_fd(2, "msh: %s\n", strerror(errno));
		return ;
	}
	env_val_set("OLDPWD", &prog->env, env_val_get("PWD", prog->env));
	newpwd = get_cwd();
	env_val_set("PWD", &prog->env, newpwd);
	env_update(prog);
	free(newpwd);
	free(path);
}
