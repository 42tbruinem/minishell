/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/03 20:49:54 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 13:44:06 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		vec_add(t_vec *vector, void *buffer)
{
	char	*new_store;

	if (vector->index >= vector->capacity)
	{
		vector->capacity *= 2;
		new_store = malloc(sizeof(vector->type_size) * (vector->capacity));
		if (!new_store)
			return (0);
		ft_memcpy(new_store, vector->store,
			(vector->type_size * vector->index));
		free(vector->store);
		vector->store = new_store;
	}
	ft_memcpy(&vector->store[vector->index * vector->type_size],
		buffer, vector->type_size);
	vector->index++;
	return (1);
}
