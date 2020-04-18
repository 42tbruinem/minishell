/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 15:08:01 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/17 16:24:02 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		main(void)
{
	char	input[] = "\"echo\" -ne \"test\" >> out.txt";
	char	*tokarray;
	size_t	i;

	tokarray[i] = ft_strtok(input, "\"kkjkj")
	ft_printf("input = %s\n", input);
	return (0);
}
