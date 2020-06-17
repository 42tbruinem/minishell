/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_update.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:59:10 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <msh_env.h>

void	env_update(t_msh *prog)
{
	ft_str2clear(prog->envp);
	prog->envp = env_convert(prog->env);
}
