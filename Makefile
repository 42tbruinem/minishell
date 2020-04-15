# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/12 11:11:07 by rlucas        #+#    #+#                  #
#    Updated: 2020/04/14 14:01:36 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBDIR = libft/
SRCDIR = src/
OBJDIR = obj/
INCLUDES = -Iincludes/ -I$(LIBDIR)includes/

SRC = $(SRCDIR)main.c \
	  $(SRCDIR)builtins.c \
	  $(SRCDIR)util1.c

OBJ = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))

FLAGS = -Wall -Wextra -Werror

# $(OBJ):
# 	@echo $(patsubst $(OBJDIR)%.o,$(SRCDIR)%.c,$@) 
#
all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling shell..."
	@gcc $(FLAGS) $(OBJ) -o $(NAME) $(INCLUDES) \
		-L$(LIBDIR) -lft

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

.PHONY: clean fclean all re bonus compile_library
