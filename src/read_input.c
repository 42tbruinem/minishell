/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 13:59:15 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

int		read_input(char **input)
{
	int		ret;

	ret = get_next_line(STDIN, input);
	ft_printf("ret = %d\nInput = %s\n", ret, *input);
	free(*input);
	return (ret);
}
