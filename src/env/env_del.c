/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_del.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:58:54 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <msh_env.h>

void	env_del(t_var *delete)
{
	free(delete->name);
	free(delete->val);
	free(delete);
}
