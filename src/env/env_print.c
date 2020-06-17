/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_print.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 19:15:39 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:59:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_env.h>

void	env_print(t_var *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
}
