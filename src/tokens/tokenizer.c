/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 23:24:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 20:11:40 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_lex.h>
#include <msh_cmd.h>

static size_t	sum_tokens(t_vecstr *line)
{
	t_lexer		lex;
	size_t		sum;

	init_lexer(&lex);
	sum = 0;
	while (vecstr_val(line, lex.i))
	{
		check_esc_char(line, &lex, 0);
		update_lexer(vecstr_get(line), &lex);
		if (lex.state >= SEMICOLON && lex.state <= PIPE_PIPE)
			lex.state = WHITESPACE;
		if (lex.state != WHITESPACE && lex.prevstate == WHITESPACE)
			sum++;
		lex.escape = 0;
		lex.i++;
	}
	return (sum);
}

static void		assign_token_indexes(char *line, t_tok *tokens)
{
	size_t		i;

	i = 0;
	while (tokens[i].value)
	{
		tokens[i].value = &line[tokens[i].index];
		i++;
	}
}

int				tokenizer(t_msh *prog, t_vecstr *line)
{
	t_tok		*tokens;
	size_t		totaltokens;

	totaltokens = sum_tokens(line);
	tokens = (t_tok *)malloc(sizeof(t_tok) * (totaltokens + 1));
	if (!tokens)
		return (0);
	if (!gen_tokens(&tokens, line, prog))
	{
		free(tokens);
		return (0);
	}
	assign_token_indexes(vecstr_get(&prog->line.cmd), tokens);
	if (!get_commands(prog, tokens, totaltokens))
	{
		free(tokens);
		exit(0);
	}
	free(tokens);
	return (1);
}
