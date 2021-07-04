# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: narakely <narakely@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 17:34:31 by narakely          #+#    #+#              #
#    Updated: 2021/06/29 20:25:31 by narakely         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1	=	so_long

NAME2	=	so_long_bonus

NAME3	= 	bonus

SRCS	=	so_long.c so_long1.c gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS_BONUS = so_long_bonus.c so_long_bonus1.c gnlbonus/get_next_line.c gnlbonus/get_next_line_utils.c

CC		=	gcc

CFLAGS	= -Wextra -Werror -Wall

RM		= rm -f

OBJS	= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME1):	${OBJS}
			${CC} -o ${NAME1} -lmlx -framework OpenGL -framework AppKit ${OBJS}

all:		${NAME1} 

clean:
			${RM} ${OBJS}
			${RM} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME1}
			${RM} ${NAME2}

re:			fclean all

$(NAME3): ${OBJS_BONUS}
			${CC} -o ${NAME2} -lmlx -framework OpenGL -framework AppKit ${OBJS_BONUS}
		
.PHONY:		all clean fclean re run