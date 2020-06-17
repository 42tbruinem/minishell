/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_new.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:58:59 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <msh_env.h>
#include <stdlib.h>

t_var	*env_new(const char *name, const char *val)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->len = ft_strlen(name) + ft_strlen(val) + 1;
	new->name = ft_strdup(name);
	if (!new->name)
		return (NULL);
	new->val = ft_strdup(val);
	if (!new->val)
		return (NULL);
	new->next = NULL;
	return (new);
}
