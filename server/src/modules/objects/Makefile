
NAME=	../../../modules/basicObjects.so

CXX=	clang++ -fpic -I../../kernel/render/ -I../includes/ -I../../kernel/modules -g3

SRC=	BasicShape.cpp	\
		Cone.cpp		\
		Cylindre.cpp	\
		Plan.cpp		\
		Sphere.cpp		\
		def.cpp			\
		../includes/UtilSdeg.cpp

OBJ=	$(SRC:.cpp=.o)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

re:	clean $(NAME)
