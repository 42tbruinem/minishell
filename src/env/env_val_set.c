/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_val_set.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 20:49:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_var	*env_val_set(const char *name, t_var *env, const char *val)
{
	while (env && env->next)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->val);
			env->val = ft_strdup(val);
			if (!env->val)
				return (NULL);
			return (env);
		}
		env = env->next;
	}
	env->next = env_new(name, val);
	return (NULL);
}
