
SRC=	objects			\
		transform		\
		basic_light		\
		advanced_light

all:
	for fileList in $(SRC) ; do \
		make -C $$fileList ; \
	done

clean:
	for fileList in $(SRC) ; do \
		make clean -C $$fileList ; \
	done

fclean:
	for fileList in $(SRC) ; do \
		make fclean -C $$fileList ; \
	done

re:	fclean all

.PHONY: all clean fclean re

