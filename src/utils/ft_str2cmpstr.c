/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str2cmpstr.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:46:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/11 21:48:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <minishell.h>

long long	ft_str2cmpstr(const char **str2, char *str)
{
	long long	i;

	i = 0;
	if (!str)
		return (-1);
	while (str2[i])
	{
		if (ft_strcmp((char *)str2[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}
