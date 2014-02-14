
NAME=	drt

all:	kernel modules

$(NAME):
	make -C src/kernel
	cp src/kernel/drt $(NAME)

kernel:	$(NAME)

modules:
	make -C src/modules

clean:
	make -C src/modules clean
	make -C src/kernel clean

fclean:
	make -C src/kernel fclean
	make -C src/modules fclean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all kernel modules clean fclean all

