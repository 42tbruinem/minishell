/* **************************************************************************
 * */
/*                                                                            */
/*                                                        ::::::::            */
/*   listutils1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 14:32:03 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 14:45:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

char	*get_env_value(const char *name, t_var *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
