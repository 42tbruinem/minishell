/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashutils1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 16:33:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 16:41:52 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

char	*get_env_value(const char *targetvar, t_env table[ENV_SIZE])
{
	int				offset;
	unsigned int	hash_value;

	offset = 0;
	hash_value = hash_42(targetvar);
	while (ft_strcmp(table[hash_value + offset].varname, targetvar) != 0)
	{
		if (table[hash_value + offset].varname == NULL)
			return (NULL);
		offset++;
		if (hash_value + offset == ENV_SIZE)
			offset = -hash_value;
		if (offset == 0)
			return (NULL);
	}
	return (table[hash_value + offset].value);
}
