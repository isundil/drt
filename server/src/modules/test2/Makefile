
NAME=	../../../modules/test2.so

CXX=	clang++ -fpic

SRC=	def.cpp

OBJ=	$(SRC:.cpp=.o)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ)

