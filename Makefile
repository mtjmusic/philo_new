CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC_DIR = src
SRCS = \
	main.c \
	init.c \
	utils.c \
	simulation.c \
	simulation_helpers.c \
	validate_input.c \
	routines.c

SRC = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
NAME = philo

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
