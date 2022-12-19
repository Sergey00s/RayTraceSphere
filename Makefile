NAME=ray
SRC = $(wildcard *.c)
INC = minirt.h
OBJECTS = $(SRC:.c=.o)
CC = gcc
CFLAGS = -I libft -I veclib
LIBFT = libft
VECLIB = veclib

all: $(NAME) 
	
 
$(NAME): libftf veclibf $(OBJECTS)
	$(CC) $(OBJECTS) libft/libft.a veclib/veclib.a -I libft -I veclib $(CFLAGS) -o $(NAME)


%.o: %.c $(INC)
	$(CC) -c $< -o $@ $(CFLAGS)

veclibf:
	make -C veclib
	
libftf:
	make -C libft

clean:
	del $(OBJECTS)

fclean: clean
	del $(NAME).exe

ffclean: fclean
	make fclean -C libft
	make fclean -C veclib

re: fclean all

.PHONY: clean all re fclean
