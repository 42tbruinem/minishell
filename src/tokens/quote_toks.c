/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_toks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 13:10:59 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/29 15:21:44 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_lex.h>

static void	slice(t_msh *prog, t_lexer *lex, t_vecstr *line)
{
	if (vecstr_slice(line, lex->i, lex->i + 1))
		error_exit(prog, MEM_FAIL);
	lex->i--;
}

void		quote_toks(t_tok **tokens, t_lexer *lex, t_vecstr *line,
		t_msh *prog)
{
	if (vecstr_slice(line, lex->i, lex->i + 1))
		error_exit(prog, MEM_FAIL);
	if (lex->prevstate == WHITESPACE)
		create_token((*tokens) + lex->tokeni, lex);
	while (vecstr_val(line, lex->i))
	{
		if (check_esc_char(line, lex, 1))
			continue ;
		if (!lex->escape && vecstr_val(line, lex->i) == '$' &&
				lex->state != INSINGLEQUOTE)
		{
			evaluate_env(lex, line, prog);
			continue ;
		}
		update_lexer(vecstr_get(line), lex);
		if (lex->state == NORMAL)
			return (slice(prog, lex, line));
		lex->escape = 0;
		lex->i++;
	}
}
