/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_esc_char.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:18:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/17 15:09:38 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_lex.h>

static int	esc_double_quotes(t_vecstr *line, t_lexer *lex, t_msh *prog)
{
	int		c;

	c = vecstr_val(line, lex->i + 1);
	if (c == '\0' || c == '$' || c == '"' || c == '`' || c == 'n' || c == '\\')
	{
		if (vecstr_slice(line, lex->i, lex->i + 1))
			error_exit(prog, MEM_FAIL);
		return (1);
	}
	lex->i++;
	return (1);
}

int			check_esc_char(t_vecstr *line, t_lexer *lex, int gen_true,
		t_msh *prog)
{
	if (vecstr_val(line, lex->i) == '\\' &&
			lex->escape == 0 && lex->state != INSINGLEQUOTE)
	{
		lex->escape = 1;
		if (gen_true && lex->state == INDOUBLEQUOTE)
			return (esc_double_quotes(line, lex, prog));
		if (gen_true)
			if (vecstr_slice(line, lex->i, lex->i + 1))
				error_exit(prog, MEM_FAIL);
		return (1);
	}
	return (0);
}
