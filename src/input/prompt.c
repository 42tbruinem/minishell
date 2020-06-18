/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:42:01 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 19:05:27 by rlucas        ########   odam.nl         */
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

	user = env_val_get("USER", prog->env, 4);
	if (user != NULL)
	{
		line->promptlen = ft_strlen(user) + 4;
		prompt = ft_str3join("\033[36;1m", user, "\033[39;0m:~$ ");
	}
	else
		prompt = ft_strdup(":~$ ");
	g_prompt = prompt;
	return (prompt);
}
