/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_destroy.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/03 20:49:54 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 13:15:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		vec_destroy(t_vec *vector, void (*del)(void *))
{
	if (del)
		del(vector);
	free(vector->store);
	vector->capacity = 0;
	vector->index = 0;
	vector->type_size = 0;
	vector->store = NULL;
	return (0);
}
