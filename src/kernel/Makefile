
SRC=	main.cpp

OBJ=	$(SRC:.cpp=.o)

NAME=	drt

CXX=	clang++

CXXFLAGS=	-W -Wall -Wextra

LDFLAGS=

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

