/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_convert.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:58:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <msh_env.h>

static size_t	env_size(t_var *env)
{
	size_t	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char			**env_convert(t_var *env)
{
	size_t	i;
	size_t	len;
	char	**envp;

	i = 0;
	len = env_size(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	while (i < len)
	{
		envp[i] = ft_str3join(env->name, "=", env->val);
		if (!envp[i])
			return (ft_str2clear(envp));
		env = env->next;
		i++;
	}
	envp[i] = 0;
	return (envp);
}
