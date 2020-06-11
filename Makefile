# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/12 11:11:07 by rlucas        #+#    #+#                  #
#    Updated: 2020/06/11 20:57:16 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBDIR = libft
SRCDIR = src
OBJDIR = obj
HEADERS = minishell.h msh_term.h
INCLUDES = -I includes/ -I $(LIBDIR)/includes/

SRC =	main.c \
		read_input.c \
		handle_input.c \
		input1.c \
		exit.c \
		add_char.c \
		delete_char.c \
		move_cursor.c \
		move_cursor2.c \
		execute.c \
		builtin/ft_cd.c \
		builtin/ft_export.c \
		builtin/ft_unset.c \
		builtin/ft_pwd.c \
		builtin/ft_echo.c \
		builtin/ft_exit.c \
		builtin/ft_env.c \
		pipeline.c \
		vector.c \
		tables.c \
		commands.c \
		env/env_init.c \
		env/env_clear.c \
		env/env_del.c \
		env/env_new.c \
		env/env_print.c \
		env/env_val_set.c \
		env/env_val_get.c \
		env/env_update.c \
		env/env_convert.c \
		env/env_unset.c \
		prompt.c \
		terminal.c \
		token.c \
		finitestatemachine.c \
		lexutils.c \
		sum_tokens.c \
		gen_tokens.c \
		utils.c \
		signals.c

OBJ := $(addprefix $(OBJDIR)/, $(SRC:%.c=%.o))
SRC := $(addprefix $(SRCDIR)/, $(SRC))

FLAGS = -Wall -Wextra -Werror
ifdef DEBUG
FLAGS += -g -fsanitize=address
endif

all: lft $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling shell..."
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(INCLUDES) -L $(LIBDIR)/ -lft -ltermcap

lft:
	@$(MAKE) -sC $(LIBDIR)/

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "Compiling $@"
	@gcc -c $(INCLUDES) $(FLAGS) $< -o $@

clean:
	@echo "Removing objects of libraries..."
	@$(MAKE) -sC $(LIBDIR)/ clean -j
	@echo "Removing objects directory..."
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Removing libraries and minishell executable..."
	@$(MAKE) -sC $(LIBDIR)/ fclean -j
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus compile_library
