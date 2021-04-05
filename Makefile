SRC = *.cpp
OBJ = $(SRC)
NAME = exe
DEBUGNAME = exefake
CXX = gcc
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror
DEBUGCXXFLAGS = -Wall -Wextra -Wpedantic -Werror -g
RM = rm -f

all:
	$(CXX)	$(OBJ) -o $(NAME) $(CXXFLAGS) $(LBFLAGS)


debug:
	$(CXX)	$(OBJ) -o $(DEBUGNAME) $(DEBUGCXXFLAGS) $(LBFLAGS)


fclean: 
	$(RM)	$(NAME)

re: fclean all

.PHONY: all fclean re