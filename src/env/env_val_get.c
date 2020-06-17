/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_val_get.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 18:57:45 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_env.h>

char	*env_val_get(const char *name, t_var *env, size_t len)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, len) == 0)
		{
			if (ft_strlen(env->name) == len)
				return (env->val);
		}
		env = env->next;
	}
	return (NULL);
}
