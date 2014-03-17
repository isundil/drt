
NAME=	../../../modules/basicTransform.so

CXX=	clang++ -fpic -I../../kernel/render/ -I../includes/ -I../../kernel/modules -g3

SRC=	BasicTransform.cpp


OBJ=	$(SRC:.cpp=.o)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ)

clean:
	rm $(OBJ)

re:	clean $(NAME)
