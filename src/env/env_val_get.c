/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_val_get.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:59:13 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_env.h>

char	*env_val_get(const char *name, t_var *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
