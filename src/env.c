/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/18 14:13:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"

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

void	env_clear(t_var *env, void (*del)(void *))
{
	t_var	*delete;

	while (env)
	{
		delete = env;
		env = env->next;
		del(delete->name);
		del(delete->val);
	}
}

void	env_print(t_var *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
}

char	*var_name(char **str)
{
	char	*new;
	char	*end_of_name;
	size_t	i;

	i = 0;
	end_of_name = ft_strchr(*str, '=');
	if (!end_of_name)
		return (NULL); //error
	new = malloc(sizeof(char) * ((end_of_name - *str) + 1));
	if (!new)
		return (NULL); //error
	while (**str && *str < end_of_name)
	{
		new[i] = **str;
		(*str)++;
		i++;
	}
	new[i] = 0;
	(*str)++;
	return (new);
}

t_var	*var_init(char *str)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->len = ft_strlen(str);
	new->name = var_name(&str);
	if (!new->name)
		return (NULL);//error
	new->val = ft_strdup(str);
	if (!new->val)
		return (NULL);//error
	new->next = NULL;
	return (new);
}

void	env_init(t_msh *prog)
{
	extern char	**environ;
	t_var		*env;
	size_t		i;

	i = 0;
	prog->env = var_init(environ[i]);
	if (!prog->env)
		return ;//error
	env = prog->env;
	while (environ[i])
	{
		env->next = var_init(environ[i]);
		if (!env->next)
			return ;//error
		env = env->next;
		i++;
	}
}
