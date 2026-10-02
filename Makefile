NAME		:= scop

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++17
LDLIBS		:= -lglfw -lGL

SRC_DIR		:= source
INC_DIR		:= header
OBJ_DIR		:= build

# source/ 아래 모든 깊이의 .cpp
SRCS		:= $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

# header/ 와 그 아래 모든 폴더를 include 경로로 추가
INC_DIRS	:= $(shell find $(INC_DIR) -type d)
CPPFLAGS	:= $(addprefix -I,$(INC_DIRS)) -MMD -MP

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
