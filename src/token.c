/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 23:24:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/11 21:15:28 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

int			add_arg(t_msh *prog, char *arg, int argtype)
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

void		assign_token_indexes(char *line, t_tok *tokens)
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
	t_tok		*tokens;
	size_t		totaltokens;

	totaltokens = sum_tokens(line);
	ft_printf("sum = %u\n", totaltokens);
	tokens = (t_tok *)malloc(sizeof(t_tok) * (totaltokens + 1));
	if (!tokens)
		return (0);
	gen_tokens(&tokens, line, prog);
	assign_token_indexes(vecstr_get(&prog->line.cmd), tokens);
	print_tokens(tokens);
	if (!get_commands(prog, tokens, totaltokens))
	{
		free(tokens);
		exit(0);
	}
	free(tokens);
	return (1);
}
