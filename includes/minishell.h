/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:51:49 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/18 14:22:22 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define MAX_TOKSIZE 300

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
	char	token[MAX_TOKSIZE];
	char	*raw;
	size_t	index;
}				t_lexer;

typedef struct s_token	t_token;

struct	s_token
{
	char	*content;
	int		type;
	t_token	*next;
};

typedef	struct	s_msh
{
	t_var		*env;
}				t_msh;

enum			e_error
{
	MEM_FAIL
};

/*
** Functions to use with lists in listutils*.c. CURRENTLY OBSOLETE.
*/

/*
** Lookup tables in tables.c.
*/

char			*error_lookup(int err);

/*
** Functions to free all allocated memory before exiting - erroneously or
** normally.
*/

char			*env_val_get(const char *name, t_var *env);
void			env_clear(t_var *env, void (*del)(void *));
void			env_init(t_msh *prog);
void			env_print(t_var *env);

void			error_exit(t_msh *prog, int err);
void			std_exit(t_msh *prog);


t_token			*tokenize(char *raw);
void			tokprint(t_token *list);

/*
** Initialization functions in init.c.
*/

void			init_env(t_msh *prog);

/*
** Core shell functions.
*/

int				read_input(char **input);

#endif
