/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:51:49 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/24 15:21:14 by rlucas        ########   odam.nl         */
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

# include <unistd.h>
# include <termios.h>

typedef struct	s_node
{
	void			*data;
	struct s_node	*next;
}				t_node;

typedef struct	s_env
{
	char		*varname;
	char		*value;
	int			duprange;
}				t_env;

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
	char			cap_table[2048];
	char			*tableptr;
	size_t			cmd_len;
	t_coord			max;
	t_coord			cursor;
	int				scroll;
	int				total_rows;
	struct termios	term;
}				t_line;

typedef	struct	s_msh
{
	t_env		env[ENV_SIZE];
}				t_msh;

enum			e_error
{
	MEM_FAIL,
	TERM_FAIL,
	CAP_FAIL
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
** Test functions in test.c that will be removed prior to submission.
*/

void			test_list(t_node *head);

/*
** Hashtable functions in hashtable.c.
*/

unsigned int	hash_42(const char *str);
int				hashtable_insert(t_env table[ENV_SIZE], char *var, char *value);
int				check_var_in_range(t_env table[ENV_SIZE], char *var, int range,
		unsigned int hash_val);
void			hashtable_print(t_env table[ENV_SIZE]);
int				hashtable_remove(t_env table[ENV_SIZE], char *var);

/*
** Functions to use with hashtables in hashutils*.c.
*/

char			*get_env_value(char *targetvar, t_env table[ENV_SIZE]);

/*
** List functions in lists.c.
*/

t_node			*new_node(void *data);
t_node			*new_list(void *data);
int				new_node_at_front(void *data, t_node **head);
int				new_node_at_back(void *data, t_node **head);

/*
** Functions to use with lists in listutils*.c. CURRENTLY deprecated.
*/

// char			*get_env_value(const char *targetvar, t_node *head);

/*
** Lookup tables in tables.c.
*/

char			*error_lookup(int err);

/*
** Functions to free all allocated memory before exiting - erroneously or
** normally.
*/

void			error_exit(t_msh *prog, int err);
void			std_exit(t_msh *prog);

/*
** Initialization functions in init.c.
*/

void			init_env(t_msh *prog);

/*
** Core shell functions.
*/

int				read_input(t_line *line, t_msh *prog);

#endif
