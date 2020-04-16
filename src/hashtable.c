/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 15:34:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 16:46:48 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

unsigned int	hash_42(const char *str)
{
	unsigned int	hash_value;
	int				len;
	int				i;

	len = ft_strlen(str);
	hash_value = 0;
	i = 0;
	while (i < len)
	{
		hash_value += str[i];
		hash_value = (hash_value * str[i]) % ENV_SIZE;
		i++;
	}
	return (hash_value);
}

void			hashtable_print(t_env table[ENV_SIZE])
{
	size_t		i;

	i = 0;
	ft_printf("Start of table\n");
	while (i < ENV_SIZE)
	{
		ft_printf("\t%d\t", i);
		if (table[i].varname == NULL)
			ft_printf("---\t---\n");
		else
			ft_printf("%s\t%s\n", table[i].varname, table[i].value);
		i++;
	}
	ft_printf("End of table\n");
}

int				hashtable_insert(t_env table[ENV_SIZE], char *var, char *value)
{
	int				offset;
	unsigned int	hash_value;

	offset = 0;
	hash_value = hash_42(var);
	while (table[hash_value + offset].varname != NULL)
	{
		offset++;
		if (hash_value + offset == ENV_SIZE)
			offset = -hash_value;
		if (offset == 0)
			return (1);
	}
	table[hash_value + offset].varname = var;
	table[hash_value + offset].value = value;
	return (0);
}
