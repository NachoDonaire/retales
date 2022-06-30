SRCS	=	flavour.c tasty.c 
OBJS	=	${SRCS:.c=.o}
NAME	=	magic.out
CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Wextra -Werror 
BUFFER  =	BUFF=18
all:	${NAME}
$(NAME):	${OBJS}
	${CC} ${CFLAGS}  -o ${NAME} ${SRCS}
clean:
	${RM} ${OBJS}
fclean:
	${RM} ${NAME}
re: fclean all
.PHONY: all clean fclean re
