DEBUG=	-g3

SRC=	main.cpp					\
		config/Config.cpp			\
		config/ConfigParam.cpp

OBJ=	$(SRC:.cpp=.o)

NAME=	./drt

CXX=	clang++ -std=c++11

CXXFLAGS=	-W -Wall -Wextra $(DEBUG)

LDFLAGS=

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

run:	all
	$(NAME)

memleaks:	all
	valgrind $(NAME)

degub:	all
	gdb $(NAME)

.PHONY:	all clean fclean re run

