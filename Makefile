CC := cc

CFLAGS := -Wall -Wextra -Werror

SRC :=	ft_printf.c \
		ft_put_str.c \
		print_format.c \
		ft_put_char.c \
		ft_intlen.c \
		ft_putnbr_hexa.c \
		ft_hexalen.c \
		ft_putpthexa.c \
		 ft_uintlen.c

OBJ := $(SRC:.c=.o)

NAME := libftprintf.a

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o : %.c ft_printf.h
	$(CC) $(CFLAGS)  -c $< -o $@

re : fclean all

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

.PHONY : all re fclean clean