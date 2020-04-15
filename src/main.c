/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 13:15:44 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/15 14:53:29 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* A file testing some of the basic ideas behind "tokens". */

#include <libft.h>

#define BUF_SIZE 64

/* strtok() tokenizes strings: takes strings, and splits it up into
 * individual chunks based on a provided divider. */

/* Most languages have some functionality to do this, in C, this */
/* is strtok(...) */

int	main(void)
{
	char	input[BUF_SIZE] = "Goku, Bulma, Vegeta: Trunks, Muten-Roshi";
	int		i;
	char	*token;

	i = 0;
	token = ft_strtok(input, "/");
	/* Each call to strtok returns a new string (separated by delimiter), */
	/* until there are no more. */
	ft_printf("%d:[%p] --- %s\n", i, token, token);

	token = ft_strtok(input, ",: ");
	ft_printf("%d:[%p] --- %s\n", i, token, token);

	while (token != NULL)
	{
		token = ft_strtok(NULL, ",: ");
		ft_printf("%d:[%p] --- %s\n", i, token, token);
	}
	ft_printf("Original string: %s\n", input);
	return (0);
}
