/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_keyevents.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:23:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:48:18 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_KEYEVENTS_H
# define MSH_KEYEVENTS_H

enum				e_direction
{
	RIGHT = -1,
	LEFT = 1,
};

# define CTRL_D 4
# define CTRL_L 12
# define CTRL_U 21
# define DEL 127
# define NEWLINE 10
# define ESC 27
# define LEFT_KEY 68
# define RIGHT_KEY 67
# define UP_KEY 65
# define DOWN_KEY 66
# define HOME 72
# define END 70

typedef int			(*t_inputf)(t_line *line, char buf[6]);

void				cursor_left(t_line *line);
void				cursor_right(t_line *line);
void				cursor_home(t_line *line);
void				cursor_end(t_line *line);
void				cursor_move_row(t_line *line, int c);
void				cursor_move_word(t_line *line, int c);
int					cursor_move(t_line *line, int c);
int					special_command(t_line *line, char buf[6]);
int					send_input(t_line *line, char buf[6]);
int					char_input(t_line *line, char buf[6]);
int					backspace(t_line *line, char buf[6]);
int					send_eof(t_line *line, char buf[6]);

#endif
