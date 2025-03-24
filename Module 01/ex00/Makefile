NAME = my_program

SRC_DIR = source
INC_DIR = include

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) main.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

CXX = c++
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)

ifeq ($(DEBUG), 1)
    CXXFLAGS += -DDEBUG
    DEBUG_MSG = "🔧 Mode DEBUG activé"
else
    DEBUG_MSG = "🚀 Mode DEBUG désactivé"
endif

ifeq ($(VERBOSE), 1)
    CXXFLAGS += -DVERBOSE
    VERBOSE_MSG = "🗣️ Mode VERBOSE activé"
else
    VERBOSE_MSG = "🔇 Mode VERBOSE désactivé"
endif

all: $(NAME)
	@echo "$(DEBUG_MSG)"
	@echo "$(VERBOSE_MSG)"

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
