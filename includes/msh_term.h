/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_term.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 01:36:41 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:42:10 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TERM_H
# define MSH_TERM_H

# include <termios.h>
# include <msh_keyevents.h>

/*
**	TERMINAL COMMANDS:
*/

# define INSERT_START "im"
# define INSERT_END "ei"
# define MOVE_HORIZONTAL "ch"
# define MOVE_COLROW "cm"
# define DELETE_START "dm"
# define DELETE_END "ed"
# define SCROLL_REV "rs"
# define CLEAR_SCREEN "cl"
# define CARRIAGE_RETURN "cr"
# define DELETE_LINE "dl"
# define DELETE_LINES "DL"
# define MOVE_ROWUP "up"
# define DELETE_CHAR "dc"
# define DELETE_CHARS "DC"
# define SCROLL_LINE "sf"
# define SCROLL_LINES "SF"
# define SCROLL_UP "sr"

int						clear_screen(t_line *line, char buf[6]);
int						clear_input(t_line *line, char buf[6]);
void					init_readline(t_msh *prog);
void					termcmd(char *command, int p1, int p2,
								int lines_affected);
int						add_char(t_line *line, char c);
int						delete_word(t_line *line);
int						delete_char(t_line *line);

#endif
