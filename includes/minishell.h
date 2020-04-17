/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 10:51:49 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/17 23:52:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_var	t_var;

struct	s_var
{
	char		*name;
	char		*val;
	size_t		len;
	t_var		*next;
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

// char			*get_env_value(const char *targetvar, t_node *head);

/*
** Lookup tables in tables.c.
*/

char			*error_lookup(int err);

/*
** Functions to free all allocated memory before exiting - erroneously or
** normally.
*/

void			env_init(t_msh *prog);
void			env_print(t_var *env);


void			error_exit(t_msh *prog, int err);
void			std_exit(t_msh *prog);

/*
** Initialization functions in init.c.
*/

void			init_env(t_msh *prog);

/*
** Core shell functions.
*/

int				read_input(char **input);

#endif
