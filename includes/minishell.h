/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:51:49 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/29 19:21:11 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*
** Key codes
*/

# define CTRL_D 4
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

# define MAX_TOKSIZE 300

# include <unistd.h>
# include <termios.h>

extern char	**g_termbuff;

typedef struct s_var	t_var;

struct	s_var
{
	char		*name;
	char		*val;
	size_t		len;
	t_var		*next;
};

typedef struct	s_lexer
{
	char		token[MAX_TOKSIZE];
	char		*raw;
	size_t		index;
}				t_lexer;

typedef struct s_token	t_token;

struct			s_token
{
	char		*content;
	int			type;
	t_token		*next;
};

typedef struct	s_coord
{
	size_t		row;
	size_t		col;
}				t_coord;

typedef struct	s_line
{
	char			*prompt;
	size_t			promptlen;
	char			*cmd;
	size_t			cmd_len;
	size_t			alloced_cmd;
	size_t			inputrow;
	t_coord			max;
	t_coord			cursor;
	size_t			total_rows;
	int				escmode;
	char			*termtype;
	char			*cap_table;
	struct termios	term;
}				t_line;

typedef	struct	s_msh
{
	t_var		*env;
	t_line		line;
}				t_msh;

enum			e_error
{
	MEM_FAIL,
	TERM_FAIL,
	CAP_FAIL
};

enum			e_tokentypes
{
	PIPE,
	TRUNC,
	APPEND,
	REDIRECT,
	ENDOFARG,
	DEFAULT,
};

typedef int		(*t_inputf)(t_line *line, char buf[6]);

/*
** Utility functions in utils.c
*/

char			*ft_realloc(char *str, size_t newsize);
char			*ft_str3join(const char *s1, const char *s2, const char *s3);

/*
** Add a prompt to the shell, in prompt.c 
*/

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
int				delete_char(t_line *line);
void			cursor_left(t_line *line);
void			cursor_right(t_line *line);
void			cursor_home(t_line *line);
void			cursor_end(t_line *line);

/*
** Lookup tables in tables.c.
*/

char			*error_lookup(int err);

/*
** Functions to free all allocated memory before exiting - erroneously or
** normally.
*/

typedef void	(*t_escapef)(t_lexer *lex, char *last);

void			error_exit(t_msh *prog, int err);
void			std_exit(t_msh *prog);

void			tokprint(t_token *list);
t_token			*tokenize(char *raw);

void			env_init(t_msh *prog);
char			*env_val_get(const char *name, t_var *env);
void			env_clear(t_var *env, void (*del)(void *));
void			env_print(t_var *env);

/*
** Functions to read input and handle line-editing. In read_input.c,
** handle_input.c, and input*.c.
*/

int				handle_input(t_line *line, char buf[6]);
int				read_input(t_msh *prog);
int				send_EOF(t_line *line, char buf[6]);
int				cursor_move(t_line *line, int c);
int				special_command(t_line *line, char buf[6]);
int				send_input(t_line *line, char buf[6]);
int				char_input(t_line *line, char buf[6]);
int				backspace(t_line *line, char buf[6]);

#endif
