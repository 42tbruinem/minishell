/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gen_tokens.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 13:10:59 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/18 01:09:12 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_lex.h>

static int	state_action(char *line, t_lexer *lex)
{
	if (lex->state == SEMICOLON || lex->state == PIPE_PIPE)
	{
		lex->cmd_num++;
		lex->cmd_present = 0;
		lex->nexttype = COMMAND;
		if (lex->state == PIPE_PIPE)
			lex->pipe = 1;
	}
	if (line[lex->i] == '>')
	{
		if (lex->nexttype == WRITEFILE || lex->nexttype == APPENDFILE)
			return (parse_error(line[lex->i]));
		if (line[lex->i + 1] == '>')
		{
			lex->nexttype = APPENDFILE;
			line[lex->i] = '\0';
			lex->i++;
		}
		else
			lex->nexttype = WRITEFILE;
	}
	if (lex->state == IREDIRECT)
		lex->nexttype = INPUT_SENDER;
	lex->state = WHITESPACE;
	return (0);
}

static int	lexer(t_tok **tokens, t_vecstr *line, t_lexer *lex, t_msh *prog)
{
	if (check_esc_char(line, lex, 1))
		return (0);
	update_lexer(vecstr_get(line), lex);
	if (!lex->escape && lex->state >= INDOUBLEQUOTE &&
			lex->state <= INSINGLEQUOTE)
		quote_toks(tokens, lex, line, prog);
	if (!lex->escape && lex->state >= SEMICOLON && lex->state <= PIPE_PIPE)
		if (state_action(vecstr_get(line), lex))
			return (0);
	if (lex->state != WHITESPACE && lex->prevstate == WHITESPACE)
		create_token((*tokens) + lex->tokeni, lex);
	if (!lex->escape && (vecstr_val(line, lex->i) == '$' ||
			vecstr_val(line, lex->i) == '~') && lex->state != INSINGLEQUOTE)
		evaluate_env(lex, line, prog);
	if (lex->state == WHITESPACE)
		vecstr_set(line, lex->i, '\0');
	lex->escape = 0;
	return (1);
}

int			gen_tokens(t_tok **tokens, t_vecstr *line, t_msh *prog)
{
	t_lexer		lex;

	init_lexer(&lex);
	while (vecstr_val(line, lex.i))
	{
		if (!lexer(tokens, line, &lex, prog))
			return (0);
		lex.i++;
	}
	(*tokens)[lex.tokeni].value = NULL;
	return (1);
}
