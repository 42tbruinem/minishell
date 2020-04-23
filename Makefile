# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/12 11:11:07 by rlucas        #+#    #+#                  #
#    Updated: 2020/04/23 23:12:35 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBDIR = libft/
SRCDIR = src/
OBJDIR = obj/
INCLUDES = -Iincludes/ -I$(LIBDIR)includes/

SRC = $(SRCDIR)main.c \
	  $(SRCDIR)read_input.c \
	  $(SRCDIR)init.c \
	  $(SRCDIR)exit.c \
	  $(SRCDIR)lists.c \
	  $(SRCDIR)hashutils1.c \
	  $(SRCDIR)tables.c \
	  $(SRCDIR)hashtable.c \
	  $(SRCDIR)tc_funcs1.c \
	  $(SRCDIR)test.c 

OBJ = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))

FLAGS = -Wall -Wextra -Werror
ifdef DEBUG
FLAGS += -g -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling shell..."
	@gcc -g $(FLAGS) $(OBJ) -o $(NAME) $(INCLUDES) \
		-L$(LIBDIR) -lft -ltermcap

compile_library:
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBDIR)

$(OBJ): compile_library
	@mkdir -p obj/
	@echo "Compiling $@"
	@gcc -c $(FLAGS) -o $@ \
		$(patsubst $(OBJDIR)%.o,$(SRCDIR)%.c,$@) \
		$(INCLUDES)

clean:
	@echo "Removing objects of libraries..."
	@$(MAKE) -C $(LIBDIR) clean
	@echo "Removing objects directory..."
	@rm -rf obj/

fclean: clean
	@echo "Removing libraries and minishell executable..."
	@$(MAKE) -C $(LIBDIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus compile_library
