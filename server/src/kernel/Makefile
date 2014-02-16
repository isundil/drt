DEBUG=	-g3

SRC=	main.cpp					\
		\
		config/Config.cpp			\
		config/ConfigParam.cpp		\
		config/UnixParser.cpp		\
		config/PeerSection.cpp		\
		config/ServerSection.cpp	\
		config/WorkerSection.cpp	\
		\
		worker/WorkerManager.cpp	\
		worker/AWorker.cpp			\
		worker/Worker.cpp			\
		worker/NetworkWorker.cpp	\
		\
		network/Socket.cpp			\
		network/ServerSocket.cpp	\
		network/PeerInfo.cpp		\
		\
		modules/ModuleManager.cpp	\
		modules/AModule.cpp

OBJ=	$(SRC:.cpp=.o)

NAME=	./drt

CXX=	clang++ -std=c++11 -DDEFAULT_PORT=11424 -DMODULE_DIRS=\""modules,../../modules/"\"

CXXFLAGS=	-W -Wall -Wextra $(DEBUG) -I./

LDFLAGS=	-lpthread -ldl

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

