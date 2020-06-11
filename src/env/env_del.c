/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_del.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 23:13:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/11 20:48:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	env_del(t_var *delete)
{
	free(delete->name);
	free(delete->val);
	free(delete);
}
