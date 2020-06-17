/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:42:01 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 16:34:06 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <msh_env.h>

/*
** Creates the prompt for minishell using the USER environment variable - or
** an empty prompt if no such variable exists.
*/

char		*prompt(t_msh *prog, t_line *line)
{
	char	*user;
	char	*prompt;

	user = env_val_get("USER", prog->env);
	if (user != NULL)
	{
		line->promptlen = ft_strlen(user) + 4;
		prompt = ft_str3join("\033[32m", user, "\033[39m:~$ ");
		g_prompt = prompt;
		if (!prompt)
			return (NULL);
		return (prompt);
	}
	else
	{
		prompt = ft_strdup(":~$ ");
		if (!prompt)
			return (NULL);
		g_prompt = prompt;
		return (prompt);
	}
}
