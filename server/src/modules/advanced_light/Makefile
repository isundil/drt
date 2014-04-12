
# NAME=	../../../modules/basicLight.so
NAME=	../../../modules/advancedLight.so

CXX=	clang++ -std=c++11 -fpic -I../../kernel/render/ -I../includes/ -I../../kernel/modules -g3 -I../../kernel/

SRC=	AdvancedLight.cpp	\
	Spot.cpp		\
	Transparency.cpp	\
	Reflection.cpp		\
	Brightness.cpp

OBJ=	$(SRC:.cpp=.o)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

re:	clean $(NAME)
