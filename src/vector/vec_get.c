/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_get.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/03 20:49:54 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 13:43:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		vec_get(t_vec *vector, void *buffer, size_t index)
{
	if (!vector || !buffer || index > vector->index)
		return (0);
	ft_memcpy(buffer,
		&vector->store[index * vector->type_size], vector->type_size);
	return (1);
}
