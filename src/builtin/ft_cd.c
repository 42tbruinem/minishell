/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 23:02:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/29 13:53:06 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <msh_builtin.h>
#include <msh_env.h>

static int		scd_home(t_msh *prog)
{
	char	*home;

	home = env_val_get("HOME", prog->env, 4);
	if (!home)
	{
		ft_printf_fd(2, "cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_printf_fd(2, "cd: %s: %s\n", strerror(errno), home);
		return (1);
	}
	env_val_set("OLDPWD", &prog->env, env_val_get("PWD", prog->env, 3));
	env_val_set("PWD", &prog->env, home);
	env_update(prog);
	return (0);
}

int				ft_cd(t_msh *prog, int argc, char **argv)
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
		return (builtin_error(argv));
	}
	env_val_set("OLDPWD", &prog->env, env_val_get("PWD", prog->env, 3));
	newpwd = get_cwd();
	env_val_set("PWD", &prog->env, newpwd);
	env_update(prog);
	free(newpwd);
	free(path);
	return (0);
}
