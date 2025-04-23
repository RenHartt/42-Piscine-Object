NAME = Simulation
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++20

SRC_DIR = source
INC_DIR = include
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
INC = $(wildcard $(INC_DIR)/*.hpp)
OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

all: $(NAME)
	@echo "$(NAME) compiled successfully!"

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "$< compiled successfully!"

$(OBJ_DIR)/%.o: %.cpp $(INC)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "$< compiled successfully!"

clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJ_DIR)
	@echo "Cleaned up successfully!"

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@echo "$(NAME) removed successfully!"

re: fclean all

.PHONY: all clean fclean re