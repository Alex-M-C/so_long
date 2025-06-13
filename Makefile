#Executable name
NAME = so_long

#Compilator and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

#Variables
FILES = main.c
OBJECTS = $(FILES:.c=.o)

#Libraries path
LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a
MINILIBXDIR = ./minilibx
MINILIBX = $(MINILIBXDIR)/libmlx.a

#Bonus marker file
BONUS_FLAG = .bonus

#Default rule: compile all
all: $(LIBFT) $(NAME)

#Rule to create the program (removes bonus flag if exists)
$(NAME): $(OBJECTS) $(LIBFT) $(MINILIBX)
	@rm -f $(BONUS_FLAG)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L$(LIBDIR) -lft -L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm

#Rule to create the needed library
$(LIBFT):
	make -C $(LIBDIR) all

$(MINILIBX):
	make -C $(MINILIBXDIR) all

#Auto compile .c into .o
%.o: %.c pipex.h $(LIBDIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

#Rule to clean all the created files
clean:
	$(MAKE) -C $(LIBDIR) clean
	rm -f $(OBJECTS) $(B_OBJECTS)

#Rule to clean all, including the library
fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	rm -f $(NAME) $(BONUS_FLAG)

#Rule to recompile all
re: fclean all

#Bonus rule - only recompiles if needed
bonus: $(LIBFT) $(MINILIBX) $(BONUS_FLAG)

$(BONUS_FLAG): $(B_OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(B_OBJECTS) -L$(LIBDIR) -lft -o $(NAME)
	@touch $(BONUS_FLAG)

#Indicates that the next rules are not files
.PHONY: all clean fclean re bonus