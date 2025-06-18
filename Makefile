#Executable name
NAME = so_long

#Compilator and flags
CC = cc
CFLAGS = -g

#Variables
FILES = main.c map_validation.c so_long_utils.c path_finder.c window.c movement.c
OBJECTS = $(FILES:.c=.o)

#Libraries path
LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a
MINILIBXDIR = ./minilibx
MINILIBX = $(MINILIBXDIR)/libmlx.a

#Default rule: compile all
all: $(LIBFT) $(NAME)

#Rule to create the program (removes bonus flag if exists)
$(NAME): $(OBJECTS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L$(LIBDIR) -lft -L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm

#Rule to create the needed library
$(LIBFT):
	make -C $(LIBDIR) all

$(MINILIBX):
	make -C $(MINILIBXDIR) all

#Auto compile .c into .o
%.o: %.c so_long.h $(LIBDIR)/libft.h
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

#Indicates that the next rules are not files
.PHONY: all clean fclean re