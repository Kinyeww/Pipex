NAME = pipex
CC = cc
CCFLAGS = -Wall -Wextra -Werror

SRCS = main.c
OBJS = $(SRCS:.c=.o)

$(NAME) = $(OBJS)
	$(CC) $(CCFLAGS) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all