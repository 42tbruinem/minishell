/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 15:34:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 20:02:29 by rlucas        ########   odam.nl         */
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

int				check_var_in_range(t_env table[ENV_SIZE], char *var, int range,
		unsigned int hash_val)
{
	while (range >= 0)
	{
		if (ft_strcmp(table[(hash_val + range) % ENV_SIZE].varname, var) == 0)
			return (range);
		range--;
	}
	return (-1);
}

int				hashtable_insert(t_env table[ENV_SIZE], char *var, char *value)
{
	int				offset;
	int				range;
	unsigned int	hash_value;

	offset = 0;
	hash_value = hash_42(var);
	range = table[hash_value].duprange;
	if (range != 0)
	{
		offset = check_var_in_range(table, var, range, hash_value);
		if (offset < 0)
			while (table[(hash_value + offset) % ENV_SIZE].varname != NULL)
			{
				offset++;
				if (offset == ENV_SIZE)
					return (1);
			}
	}
	free(table[(hash_value + offset) % ENV_SIZE].varname);
	free(table[(hash_value + offset) % ENV_SIZE].value);
	table[(hash_value + offset) % ENV_SIZE].varname = var;
	table[(hash_value + offset) % ENV_SIZE].value = value;
	if (offset > 0 && offset > table[hash_value].duprange)
		table[hash_value].duprange = offset;
	return (0);
}

int				hashtable_remove(t_env table[ENV_SIZE], char *var)
{
	int				offset;
	int				range;
	unsigned int	hash_value;

	offset = 0;
	hash_value = hash_42(var);
	range = table[hash_value].duprange;
	if (range != 0)
	{
		offset = check_var_in_range(table, var, range, hash_value);
		if (offset < 0)
			return (1);
	}
	if (ft_strcmp(table[(hash_value + offset) % ENV_SIZE].varname, var) == 0)
	{
		free(table[(hash_value + offset) % ENV_SIZE].varname);
		free(table[(hash_value + offset) % ENV_SIZE].value);
		table[(hash_value + offset) % ENV_SIZE].varname = NULL;
		table[(hash_value + offset) % ENV_SIZE].value = NULL;
		return (0);
	}
	return (1);
}
