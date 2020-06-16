/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_no_ansi_strlen.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 14:58:06 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/16 14:58:32 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sys/types.h"

size_t		ft_no_ansi_strlen(const char *str)
{
	size_t		i;
	size_t		len;
	int			inansi;

	i = 0;
	len = 0;
	inansi = 0;
	while (str[i])
	{
		if (str[i] == '\033')
			inansi = 1;
		if (!inansi)
			len++;
		if (inansi == 1 && str[i] == 'm')
			inansi = 0;
		i++;
	}
	return (len);
}
