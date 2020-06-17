/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_lex.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:48:07 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:38:44 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_LEX_H
# define MSH_LEX_H

# include <minishell.h>
# include <sys/types.h>
# include <libft.h>

enum					e_fsm
{
	NORMAL = 0,
	WHITESPACE,
	INDOUBLEQUOTE,
	INSINGLEQUOTE,
	INBACKTICK,
	SEMICOLON,
	OREDIRECT,
	IREDIRECT,
	OAPPEND,
	PIPE_PIPE,
	ENV
};

enum				e_toktype
{
	COMMAND = 0,
	STANDARD,
	WRITEFILE,
	APPENDFILE,
	SEPARATOR,
	PIPEDCOMMAND,
	INPUT_SENDER
};

typedef struct		s_lexer
{
	size_t			i;
	size_t			j;
	int				prevstate;
	int				state;
	int				escape;
	size_t			tokeni;
	int				nexttype;
	int				cmd_num;
	int				cmd_present;
	int				pipe;
}					t_lexer;

typedef	struct		s_tok
{
	int				type;
	size_t			index;
	char			*value;
	int				cmd_num;
}					t_tok;

void				env_exitstatus(t_lexer *lex, t_vecstr *line,
									t_msh *prog);
void				env_current_process(t_lexer *lex, t_vecstr *line,
									t_msh *prog);
void				evaluate_env(t_lexer *lex, t_vecstr *line, t_msh *prog);
size_t				env_strclen(char *line, const char *chars);
int					parse_error(char c);
int					conv_tokens(t_msh *prog, t_tok *tokens,
								size_t totaltokens);
void				quote_toks(t_tok **tokens, t_lexer *lex, t_vecstr *line,
								t_msh *prog);
int					tokenizer(t_msh *prog, t_vecstr *line);
int					gen_tokens(t_tok **tokens, t_vecstr *line, t_msh *prog);
int					lex_checkstate(int c, t_lexer lex);
int					check_esc_char(t_vecstr *line, t_lexer *lex, int gen_true,
									t_msh *prog);
void				init_lexer(t_lexer *lex);
void				update_lexer(char *line, t_lexer *lex);
void				create_token(t_tok *token, t_lexer *lex);
void				concatenate_input(char *line);

#endif
