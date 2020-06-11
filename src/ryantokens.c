/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ryantokens.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 23:24:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/10 21:18:28 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

//ARG AND ARGTYPES IS INSIDE THE PROG STRUCT, NEED TO CHANGE TOKENIZER TO CREATE THE COMMAND LIST

//first get an array of args and argtypes from the tokens, with a NULL inbetween the commands

int			add_arg(t_msh *prog, char *arg, int argtype)
{
	if (!vec_add(&prog->args, &arg))
		return (vec_destroy(&prog->args, NULL));
	if (!vec_add(&prog->argtypes, &argtype))
		return (vec_destroy(&prog->argtypes, NULL));
	return (1);
}

int			conv_tokens(t_msh *prog, t_ryantok *tokens, size_t totaltokens)
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

void		assign_token_indexes(char *line, t_ryantok *tokens)
{
	size_t		i;

	i = 0;
	while (tokens[i].value)
	{
		tokens[i].value = &line[tokens[i].index];
		i++;
	}
}

int			tokenizer(t_msh *prog, t_vecstr *line)
{
	t_ryantok		*tokens;
	size_t			totaltokens;

	totaltokens = sum_tokens(line); //token amount
	ft_printf("sum = %u\n", totaltokens);
	tokens = (t_ryantok *)malloc(sizeof(t_ryantok) * (totaltokens + 1)); //malloc tokens
	if (!tokens)
		return (0);
	gen_tokens(&tokens, line, prog); //assign tokens
	assign_token_indexes(vecstr_get(&prog->line.cmd), tokens);
	print_tokens(tokens);
	if (!get_commands(prog, tokens, totaltokens))
	{
		free(tokens);
		return (0);
	}
	free(tokens);
	return (1);
}
