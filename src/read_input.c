/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:50:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/18 14:25:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

int		read_input(char **input)
{
	int		ret;
	t_token	*tok;

	ret = get_next_line(STDIN, input);
	ft_printf("ret = %d\nInput = %s\n", ret, *input);
	if (ret >= 0)
	{
		tok = tokenize(*input);
		tokprint(tok);
	}
	free(*input);
	return (ret);
}
