/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/17 23:58:05 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"

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
	size_t	i;

	i = 0;
	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->len = ft_strlen(str);
	new->name = var_name(&str);
	new->val = ft_strdup(str);
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
		env = env->next;
		i++;
	}
}
