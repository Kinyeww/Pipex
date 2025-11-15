NAME = pipex
CC = cc
CCFLAGS = -Wall -Wextra -Wextra

SRCS = pipex.c ft_printf/ft_printf_utils.c ft_printf/ft_printf.c ft_split.c pipex_utils.c pipex_utils2.c
OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all