
NAME=	../../../modules/basicLight.so


CXX=	clang++ -std=c++11 -fpic -I../../kernel/render/ -I../includes/ -I../../kernel/modules -g3 -I../../kernel/

SRC=	BasicLight.cpp	\
	Spot.cpp

OBJ=	$(SRC:.cpp=.o)

SRC2=	BasicLight.cpp	\
	../advanced_light/Spot.cpp

OBJ2=	$(SRC2:.cpp=.o)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ)

advanced:	$(OBJ2)
	$(CXX) -shared -o $(NAME) $(OBJ2)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ2)

fclean: clean
	rm -rfv $(NAME)

re:	fclean $(NAME)
