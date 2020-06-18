/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_val_set.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/18 14:10:29 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_env.h>

int				check_last(const char *name, t_var *iter, const char *val)
{
	if (ft_strcmp(iter->name, name) == 0)
	{
		free(iter->val);
		iter->val = ft_strdup(val);
		return (1);
	}
	return (0);
}

t_var			*env_val_set(const char *name, t_var **env, const char *val)
{
	t_var	*iter;

	iter = *env;
	while (iter && iter->next)
	{
		if (ft_strcmp(iter->name, name) == 0)
		{
			free(iter->val);
			iter->val = ft_strdup(val);
			if (!iter->val)
				return (NULL);
			return (iter);
		}
		iter = iter->next;
	}
	if (iter == *env)
	{
		*env = env_new(name, val);
		return (*env);
	}
	if (check_last(name, iter, val))
		return (iter->val ? iter : NULL);
	iter->next = env_new(name, val);
	return (iter->next);
}
