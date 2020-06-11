/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str2print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:46:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/11 21:47:51 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <minishell.h>

void		ft_str2print(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		ft_printf("%s%c", str[i], (str[i + 1]) ? ' ' : '\n');
		i++;
	}
}
