/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 20:48:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static	char	*var_name(char **str)
{
	char	*new;
	char	*end_of_name;
	size_t	i;

	i = 0;
	end_of_name = ft_strchr(*str, '=');
	if (!end_of_name)
		return (NULL);
	new = malloc(sizeof(char) * ((end_of_name - *str) + 1));
	if (!new)
		return (NULL);
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

static	t_var	*var_init(char *str)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->len = ft_strlen(str);
	new->name = var_name(&str);
	if (!new->name)
		return (NULL);
	new->val = ft_strdup(str);
	if (!new->val)
		return (NULL);
	new->next = NULL;
	return (new);
}

int				env_init(t_msh *prog)
{
	extern char	**environ;
	t_var		*env;
	size_t		i;

	i = 0;
	prog->env = var_init(environ[i]);
	if (!prog->env)
		return (env_clear(prog->env, &free));
	env = prog->env;
	while (environ[i])
	{
		env->next = var_init(environ[i]);
		if (!env->next)
			return (env_clear(prog->env, &free));
		env = env->next;
		i++;
	}
	prog->envp = env_convert(prog->env);
	if (!prog->envp)
		return (0);
	return (1);
}
