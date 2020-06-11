/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_clear.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 19:16:07 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_clear(t_var *env, void (*del)(void *))
{
	t_var	*delete;

	while (env)
	{
		delete = env;
		env = env->next;
		del(delete->name);
		del(delete->val);
	}
	return (0);
}
