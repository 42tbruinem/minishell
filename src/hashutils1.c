/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashutils1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 16:33:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 19:59:45 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

char	*get_env_value(char *targetvar, t_env table[ENV_SIZE])
{
	int				offset;
	int				range;
	unsigned int	hash_value;

	offset = 0;
	hash_value = hash_42(targetvar);
	range = table[hash_value].duprange;
	if (range != 0)
	{
		offset = check_var_in_range(table, targetvar, range, hash_value);
		if (offset < 0)
			while (table[(hash_value + offset) % ENV_SIZE].varname != NULL)
			{
				offset++;
				if (offset == ENV_SIZE)
					return (NULL);
			}
	}
	if (offset == -1)
		return (NULL);
	return (table[hash_value + offset].value);
}
