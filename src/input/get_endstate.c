/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_endstate.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/23 18:36:37 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/23 18:39:53 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <msh_lex.h>
#include <minishell.h>

static void	state_update(t_lexer *lex)
{
	if (lex->state == PIPE_PIPE)
		lex->pipe = 1;
	if (lex->state >= SEMICOLON && lex->state <= PIPE_PIPE)
		lex->state = WHITESPACE;
	if (lex->state != WHITESPACE && lex->prevstate == WHITESPACE)
		lex->pipe = 0;
}

int			get_endstate(t_vecstr *line)
{
	t_lexer		lex;

	init_lexer(&lex);
	while (vecstr_val(line, lex.i))
	{
		if (check_esc_char(line, &lex, 0))
			return (-1);
		if (lex.escape == 1)
		{
			if (lex.i + 1 >= vecstr_len(line))
				return (lex.state);
			lex.i++;
		}
		update_lexer(vecstr_get(line), &lex);
		state_update(&lex);
		lex.escape = 0;
		lex.i++;
	}
	if (lex.pipe)
		return (PIPE_PIPE);
	return (lex.state);
}
