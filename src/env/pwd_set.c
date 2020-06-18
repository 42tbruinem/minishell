/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 13:41:12 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/18 13:54:34 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <msh_env.h>
#include <msh_builtin.h>
#include <stdlib.h>

int		pwd_set(t_var **env)
{
	char		*pwd;

	pwd = get_cwd();
	if (!pwd)
		return (0);
	if (!env_val_set("PWD", env, pwd))
	{
		free(pwd);
		return (0);
	}
	free(pwd);
	return (1);
}
