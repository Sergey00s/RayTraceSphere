NAME	= veclib
CC		= gcc
INC		= vec3d.h
CFLAGS	= -Wall -Wextra -Werror
ARFLAGS	= -rcs
RM		= del

SRCS	= vec3d.c

OBJS = $(SRCS:.c=.o)

all: $(NAME).a

$(NAME).a: $(OBJS)
	ar $(ARFLAGS) $(NAME).a $(OBJS)

%.o: %.c $(INC)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME).a

re: fclean all

.PHONY: all clean fclean re norm watch