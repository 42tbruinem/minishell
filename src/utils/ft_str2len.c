/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str2len.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:46:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/11 21:47:34 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <minishell.h>

size_t		ft_str2len(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
