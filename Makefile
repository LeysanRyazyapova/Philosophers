SRCS	=	philo.c \
			philo_utils.c \
			life.c \
			timer.c

HEADER	=	philo.h

OBJS	=	${SRCS:.c=.o}

NAME	=	philo

CC		=	gcc

RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -MMD

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

.PHONY: all
all:		${NAME}

$(NAME):	${OBJS} ${HEADER}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

.PHONY: clean
clean:	
			${RM} ${OBJS}
			${RM} $(OBJS:.o=.d)

.PHONY: fclean
fclean:		clean
			${RM} ${NAME}

.PHONY: re
re:			fclean all
-include	$(OBJS:.o=.d)