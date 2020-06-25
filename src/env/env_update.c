/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_update.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/25 15:20:40 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <msh_env.h>
#include <stdlib.h>

void	env_update(t_msh *prog)
{
	ft_str2clear(prog->envp);
	prog->envp = env_convert(prog->env);
	if (!prog->envp)
	{
		(env_clear(prog->env, &free));
		exit(1);
	}
}
