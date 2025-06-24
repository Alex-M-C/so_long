#Executable name
NAME = so_long

#Compilator and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

#Variables
FILES = main.c map_validation.c so_long_utils.c path_finder.c window.c movement.c
OBJ_NORMAL = $(FILES:.c=.o)
FILES_BONUS = bonus/main_bonus.c bonus/map_validation_bonus.c bonus/so_long_utils_bonus.c \
				bonus/path_finder_bonus.c bonus/window_bonus.c bonus/movement_bonus.c
OBJ_BONUS = $(FILES_BONUS:.c=.o)

#Libraries path
LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a
MINILIBXDIR = ./minilibx
MINILIBX = $(MINILIBXDIR)/libmlx.a

# Mode marker files
MARKER_NORMAL = .normal_build
MARKER_BONUS = .bonus_build

# Default rule (normal build)
all: $(NAME)

$(NAME): $(MARKER_NORMAL)

# Bonus rule (independent)
bonus: $(MARKER_BONUS)

# Build normal mode
$(MARKER_NORMAL): $(OBJ_NORMAL) $(LIBFT) $(MINILIBX)
	@rm -f $(OBJ_BONUS) $(MARKER_BONUS)
	$(CC) $(CFLAGS) $(OBJ_NORMAL) -o $(NAME) -L$(LIBDIR) -lft -L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm
	@touch $(MARKER_NORMAL)

# Build bonus mode
$(MARKER_BONUS): $(OBJ_BONUS) $(LIBFT) $(MINILIBX)
	@rm -f $(OBJ_NORMAL) $(MARKER_NORMAL)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME) -L$(LIBDIR) -lft -L$(MINILIBXDIR) -lmlx -lXext -lX11 -lm
	@touch $(MARKER_BONUS)

#Rule to create the needed library
$(LIBFT):
	$(MAKE) -C $(LIBDIR) all

$(MINILIBX):
	$(MAKE) -C $(MINILIBXDIR) all

#Auto compile .c into .o
%.o: %.c so_long.h $(LIBDIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

#Rule to clean all the created files
clean:
	$(MAKE) -C $(LIBDIR) clean
	$(MAKE) -C $(MINILIBXDIR) clean
	rm -f $(OBJ_NORMAL) $(OBJ_BONUS)
	rm -f $(MARKER_NORMAL) $(MARKER_BONUS)

#Rule to clean all, including the library
fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	rm -f $(NAME)

#Rule to recompile all
re: fclean all

#Indicates that the next rules are not files
.PHONY: all clean fclean re bonus