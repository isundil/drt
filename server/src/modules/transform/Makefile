
NAME=	../../../modules/basicTransform.so

CXX=	clang++ -std=c++11 -fpic -I../../kernel/render/ -I../includes/ -I../../kernel/modules -g3

SRC=	BasicTransform.cpp	\
	Translation.cpp		\
	Rotation.hpp

OBJ=	$(SRC:.cpp=.o)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ)

clean:
	rm $(OBJ)

re:	clean $(NAME)
