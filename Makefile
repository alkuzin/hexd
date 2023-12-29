CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wno-implicit-function-declaration

NAME=hexd

SRC_PATH=src/

OBJS = hexd.o

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) main.c $(OBJS) -o $(NAME)

all: $(NAME)

hexd.o: $(SRC_PATH)hexd.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)hexd.c

clean:
	rm $(OBJS)

fclean:
	rm $(NAME)
