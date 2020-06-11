/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:51:49 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/11 20:34:39 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define RIGHT -1
# define LEFT 1

/*
** Key codes
*/

# define CTRL_D 4
# define CTRL_L 12
# define CTRL_U 21
# define DEL 127
# define NEWLINE 10
# define ESC 27
# define CTRL 49
# define LEFT_KEY 68
# define RIGHT_KEY 67
# define UP_KEY 65
# define DOWN_KEY 66
# define HOME 72
# define END 70

# include <unistd.h>
# include <termios.h>
# include <libft_types.h>

enum			e_toktype
{
	COMMAND = 0,
	STANDARD,
	WRITEFILE,
	APPENDFILE,
	SEPARATOR,
	PIPEDCOMMAND,
	INPUT_SENDER
};

enum			e_fsm
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

typedef struct s_var	t_var;

struct	s_var
{
	char		*name;
	char		*val;
	size_t		len;
	t_var		*next;
};

typedef struct s_vec	t_vec;

struct	s_vec
{
	char			*store;
	size_t			type_size;
	size_t			capacity;
	size_t			index;
};

typedef struct s_arg	t_arg;

struct	s_arg
{
	t_vec	val;
	t_vec	type;
};

typedef struct s_cmd	t_cmd;

struct			s_cmd
{
	char	**args;
	int		*argtypes;
	int		cmdtype;
	int		iostream[2];
	int		cmdpipe[2];
	t_cmd	*next;
};

typedef struct	s_tok	t_tok;

struct			s_tok
{
	int			type;
	size_t		index;
	char		*value;
	int			cmd_num;
};

typedef struct	s_lexer
{
	size_t		i;
	size_t		j;
	int			prevstate;
	int			state;
	int			escape;
	size_t		tokeni;
	int			nexttype;
	int			cmd_num;
	int			cmd_present;
	int			pipe;
}				t_lexer;

typedef struct	s_coord
{
	size_t		row;
	size_t		col;
}				t_coord;

typedef struct	s_line
{
	char			*prompt;
	size_t			promptlen;
	t_vecstr		cmd;
	size_t			cmd_len;
	size_t			alloced_cmd;
	size_t			inputrow;
	t_coord			max;
	t_coord			cursor;
	size_t			total_rows;
	int				escmode;
	char			*termtype;
	char			cap_table[2048];
	struct termios	term;
}				t_line;

typedef	struct	s_msh
{
	t_vec		file_arr;
	t_vec		argtypes;
	t_vec		args;
	t_cmd		*commands;
	int			exit_status;
	char		**envp;
	t_var		*env;
	t_line		line;
	size_t		argc;
}				t_msh;

enum			e_error
{
	MEM_FAIL,
	TERM_FAIL,
	CAP_FAIL
};

enum			e_stages
{
	PRE_ENV,
	IN_ENV,
	IN_TERM,
	IN_INPUT
};

enum			e_builtins
{
	B_CD,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_ENV,
	B_UNSET,
	B_EXIT,
};

enum			e_pipe
{
	READ,
	WRITE,
};

enum			e_tokentypes
{
	PIPE,
	APPEND,
	TRUNC,
	IN_REDIR,
	EOC,
	DEFAULT,
};

t_vec	g_pid;

typedef void	(*t_builtin)(t_msh *prog, int argc, char **argv);
typedef int		(*t_inputf)(t_line *line, char buf[6]);

/*
** Utility functions in utils.c
*/

char			*ft_str3join(const char *s1, const char *s2, const char *s3);
void			print_tokens(t_tok *tokens);

/*
** Add a prompt to the shell, in prompt.c 
*/

size_t			ft_no_ansi_strlen(const char *str);
char			*prompt(t_msh *prog, t_line *line);

/*
** Initialise terminal, in terminal.c
*/

int				init_term(struct termios *term);
void			init_readline(t_msh *prog);

/*
** Functions to handle input and line editing. In add_char.c, delete_char.c,
** and move_cursor.c.
*/

int				add_char(t_line *line, char c);
int				esc_delete(t_line *line);
int				delete_char(t_line *line);
void			cursor_left(t_line *line);
void			cursor_right(t_line *line);
void			cursor_home(t_line *line);
void			cursor_end(t_line *line);
void			cursor_move_row(t_line *line, int c);
void			cursor_move_word(t_line *line, int c);

/*
** Lookup tables in tables.c.
*/

char			*error_lookup(int err);

/*
** Functions to free all allocated memory before exiting - erroneously or
** normally.
*/

typedef void	(*t_escapef)(t_lexer *lex, char *last);

void			ft_str2print(char **str);
int				execute(t_msh *prog, t_cmd *cmd);
char			**ft_str2clear(char **str);
int				clear_commands(t_cmd *commands);
int				conv_tokens(t_msh *prog, t_tok *tokens, size_t totaltokens);
int				get_commands(t_msh *prog, t_tok *tokens, size_t totaltokens);
void			print_command(t_cmd *command);
int				set_redirection(t_cmd *command, char **args,
								int *types, t_vec *fd_arr);

void			error_exit(t_msh *prog, int err, int stage);
void			std_exit(t_msh *prog);

int				vec_add(t_vec *vector, void *buffer);
int				vec_new(t_vec *vector, size_t type_size);
int				vec_destroy(t_vec *vector, void (*del)(void *));
int				vec_get(t_vec *vector, void *buffer, size_t index);

int				tokenize(t_vec *args, t_vec *argtypes, char *raw);

void			close_all(t_vec *fd_arr);
void			close_iostream(int *iostream);
void			close_ifnot(t_vec *fd_arr, int *iostream);
void			print_filearr(t_vec *fd_arr);

void			env_del(t_var *delete);
t_var			*env_new(const char *name, const char *val);
void			env_print(t_var *env);
void			env_update(t_msh *prog);
void			env_unset(t_var **env, char *name);
char			**env_convert(t_var *env);
t_var			*env_val_set(const char *name, t_var *env, const char *val);
int				env_init(t_msh *prog);
char			*env_val_get(const char *name, t_var *env);
int				env_clear(t_var *env, void (*del)(void *));

void			ft_cd(t_msh *prog, int argc, char **argv);
void			ft_pwd(t_msh *prog, int argc, char **argv);
void			ft_env(t_msh *prog, int argc, char **argv);
void			ft_echo(t_msh *prog, int argc, char **argv);
void			ft_unset(t_msh *prog, int argc, char **argv);
void			ft_exit(t_msh *prog, int argc, char **argv);
void			ft_export(t_msh *prog, int argc, char **argv);



/*
** New token functions - creates tokens using the same
** allocated string from input.
*/

int				tokenizer(t_msh *prog, t_vecstr *line);
size_t			sum_tokens(t_vecstr *line);
void			gen_tokens(t_tok **tokens, t_vecstr *line, t_msh *prog);

/*
** Functions to read input and handle line-editing. In read_input.c,
** handle_input.c, and input*.c.
*/

int				handle_input(t_line *line, char buf[6]);
int				read_input(t_msh *prog);
int				send_EOF(t_line *line, char buf[6]);
int				clear_screen(t_line *line, char buf[6]);
int				clear_input(t_line *line, char buf[6]);
int				cursor_move(t_line *line, int c);
int				special_command(t_line *line, char buf[6]);
int				send_input(t_line *line, char buf[6]);
int				char_input(t_line *line, char buf[6]);
int				backspace(t_line *line, char buf[6]);

/*
** Finite state machine function.
*/

int				checkstate(int c, t_lexer lex);

/*
** Lexing utilities.
*/

int				check_esc_char(t_vecstr *line, t_lexer *lex, int gen_true);
void			init_lexer(t_lexer *lex);
void			update_lexer(char *line, t_lexer *lex);
void			create_token(t_tok *token, t_lexer *lex);
void			concatenate_input(char *line);

/*
** Signal functions.
*/

void			sighandler(int signal);

/* Troubleshooting */
void			print_state(int c, t_lexer lex);

#endif
