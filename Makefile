CC := CC

CFLAGS :=  -Wall -Wextra -Werror

SRC := ft_printf.c /

OBJ := $(SRC:.c=.o)

NAME := libftprintf.a

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o : %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

re : fclean all

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

.PHONY : all re fclean clean