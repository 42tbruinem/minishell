/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conv_tokens.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 23:24:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/16 14:36:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

static int	add_arg(t_msh *prog, char *arg, int argtype)
{
	if (!vec_add(&prog->args, &arg))
		return (vec_destroy(&prog->args, NULL));
	if (!vec_add(&prog->argtypes, &argtype))
		return (vec_destroy(&prog->argtypes, NULL));
	return (1);
}

int			conv_tokens(t_msh *prog, t_tok *tokens, size_t totaltokens)
{
	size_t	i;
	int		cmd;

	cmd = 0;
	i = 0;
	if (!vec_new(&prog->args, sizeof(char *)))
		return (0);
	if (!vec_new(&prog->argtypes, sizeof(int)))
		return (0);
	while (i < totaltokens)
	{
		if (cmd != tokens[i].cmd_num)
		{
			if (!add_arg(prog, NULL, SEPARATOR))
				return (0);
			cmd++;
		}
		if (!add_arg(prog, tokens[i].value, tokens[i].type))
			return (0);
		i++;
	}
	return (add_arg(prog, NULL, SEPARATOR));
}
