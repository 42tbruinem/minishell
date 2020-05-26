/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexutils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:18:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/05/20 16:35:28 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

void		init_lexer(t_ryanlexer *lex)
{
	lex->i = 0;
	lex->j = 0;
	lex->state = WHITESPACE;
	lex->escape = 0;
	lex->inwhitespace = 1;
	lex->tokeni = 0;
	lex->nexttype = COMMAND;
	lex->command_present = 0;
	lex->quotes = NONE;
	lex->cmd_num = 0;
	lex->pipe = 0;
	lex->env = 0;
}

void		update_lexer(char *line, t_ryanlexer *lex)
{
	lex->prevstate = lex->state;
	lex->state = checkstate(line[lex->i], *lex);
	if (lex->prevstate == NORMAL && lex->state != NORMAL)
		lex->j = lex->i;
}

int			check_esc_char(char *line, t_ryanlexer *lex)
{
	if (line[lex->i] == '\\' && lex->escape == 0 && lex->state != INSINGLEQUOTE)
	{
		lex->escape = 1;
		lex->i++;
		return (1);
	}
	return (0);
}

static void	assign_tok_type(t_ryantok *token, t_ryanlexer *lex)
{
	if (lex->nexttype == COMMAND)
	{
		lex->command_present = 1;
		if (lex->pipe == 1)
			lex->nexttype = PIPEDCOMMAND;
		lex->pipe = 0;
	}
	token->type = lex->nexttype;
	if (lex->command_present == 0)
		lex->nexttype = COMMAND;
	else
		lex->nexttype = STANDARD;
}

void	create_token(char *value, t_ryantok *token, t_ryanlexer *lex)
{
	token->value = value;
	token->quotes = lex->quotes;
	token->cmd_num = lex->cmd_num;
	token->env = lex->env;
	assign_tok_type(token, lex);
	lex->tokeni++;
	lex->inwhitespace = 0;
	lex->env = 0;
}
