/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:51:49 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/28 01:28:14 by tbruinem      ########   odam.nl         */
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

/*
** For scroll direction when using SCROLL in tputs.
*/

# define SCROLLDOWN 1

# define ENV_SIZE 200
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
	int			row;
	int			col;
}				t_coord;

typedef struct	s_line
{
	char			*prompt;
	size_t			promptlen;
	char			*cmd;
	char			*termtype;
	char			*cap_table;
	size_t			cmd_len;
	t_coord			max;
	t_coord			cursor;
	int				scroll;
	int				total_rows;
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

/*
** TERMCAPS FUNCTIONS: in tc_funcs*.c
*/

void			refresh(t_line *line);
int				add_char(t_line *line, char buf[6]);
int				delete_char(t_line *line);
int				cursor_left(t_line *line);
int				cursor_right(t_line *line);

/*
** Lookup tables in tables.c.
*/

char			*error_lookup(int err);

/*
** Functions to free all allocated memory before exiting - erroneously or
** normally.
*/

typedef void	(*t_escapef)(t_lexer *lex, char *last);

char			*ft_str3join(const char *s1, const char *s2, const char *s3);

void			error_exit(t_msh *prog, int err);
void			std_exit(t_msh *prog);

void			tokprint(t_token *list);
t_token			*tokenize(char *raw);

void			env_init(t_msh *prog);
char			*env_val_get(const char *name, t_var *env);
void			env_clear(t_var *env, void (*del)(void *));
void			env_print(t_var *env);

/*
** Core shell functions.
*/

int				read_input(t_line *line, t_msh *prog);

#endif
