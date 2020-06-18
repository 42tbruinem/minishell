/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/18 13:37:00 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_env.h>

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

int				modify_shlvl(t_var *env)
{
	t_var		*current;
	char		*new;
	int			lvl;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, "SHLVL") == 0)
		{
			lvl = ft_atoi(current->val);
			new = ft_itoa(lvl + 1);
			if (!new)
				return (1);
			free(current->val);
			current->val = new;
			return (0);
		}
		current = current->next;
	}
	if (current)
		current->next = env_new("SHLVL", "1");
	return (0);
}

static int		env_init_head(t_msh *prog, char **environ)
{
	prog->env = NULL;
	if (!environ || !environ[0])
		return (1);
	prog->env = var_init(environ[0]);
	if (!prog->env)
		return (env_clear(prog->env, &free));
	return (-1);
}

int				env_init(t_msh *prog)
{
	extern char	**environ;
	t_var		*env;
	int			i;

	i = env_init_head(prog, environ);
	if (i != -1)
		return (i);
	i = 1;
	env = prog->env;
	while (environ[i])
	{
		env->next = var_init(environ[i]);
		if (!env->next)
			return (env_clear(prog->env, &free));
		env = env->next;
		i++;
	}
	if (modify_shlvl(prog->env))
		return (env_clear(prog->env, &free));
	prog->envp = env_convert(prog->env);
	if (!prog->envp)
		return (env_clear(prog->env, &free));
	return (1);
}
