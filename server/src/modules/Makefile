
SRC=	test 	\
		test2	\
		objects

all:
	for fileList in $(SRC) ; do \
		make -C $$fileList ; \
	done

clean:

fclean:

re:	fclean all

.PHONY: all clean fclean re

