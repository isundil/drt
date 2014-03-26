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
		worker/ManagedScene.cpp		\
		\
		network/Socket.cpp			\
		network/ServerSocket.cpp	\
		network/PeerInfo.cpp		\
		network/NetworkPacket.cpp	\
		\
		modules/ModuleManager.cpp	\
		modules/AModule.cpp			\
		\
		system/CpuUsage.cpp			\
		system/MemUsage.cpp			\
		\
		render/Scene.cpp		\
		render/camera.cpp \
		render/ray.cpp

OBJ=	$(SRC:.cpp=.o)

NAME=	./drt

CXX=	clang++ -std=c++11 -DDEFAULT_PORT=11424 -DMODULE_DIRS=\""modules,../../modules/"\"

CXXFLAGS=	-W -Wall -Wextra $(DEBUG) -I./ -I./render

LDFLAGS=	-lpthread -ldl -rdynamic

$(NAME):	$(OBJ) tags
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME) tags

tags:
	if [[ -f /bin/ctags ]]; \
		then ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ -f tags `find . -name '*.hpp'`;\
	fi

re:	fclean all

run:	all
	$(NAME)

memleaks:	all
	valgrind $(NAME)

degub:	all
	gdb $(NAME)

.PHONY:	all clean fclean re run

