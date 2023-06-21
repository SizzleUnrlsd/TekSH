##
## EPITECH PROJECT, 2023
## B-PSU-100-RUN-1-1-bsnavy-hugo.payet
## File description:
## Makefile
##

SRC	=	$(shell find ./src -name "*.c")

PLUG =	plugins/add_ons/loader.c

CC	=	gcc

OBJ	=	$(SRC:.c=.o) $(PLUG:.c=.o)

NAME	=	teksh

CFLAGS 	=	-W -Wall -Wextra -Werror -pedantic -g3 -Os -I./include/ -lreadline -lncurses

MEMORY_FLAG	=	-Wpadded

NODEADCODE	=	-fdata-sections -ffunction-sections -Wl,--gc-sections

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	ARCH := $(shell uname -p)
else
	ARCH := $(shell uname -m)
endif

ifeq ($(ARCH),x86_64)
	CFLAGS += -m64
else ifeq ($(ARCH),i386)
	CFLAGS += -m32
else ifeq ($(ARCH),armv7l)
	CFLAGS += -march=armv7-a -mfloat-abi=hard -mfpu=vfpv3-d16
else ifeq ($(ARCH),aarch64)
	CFLAGS += -march=armv8-a+simd -mcpu=cortex-a53+crypto
else
	$(error Architecture not supported : $(ARCH))
endif

%.o: %.c
	$(CC) $(CFLAGS) $(MEMORY_FLAG) $(NODEADCODE) -c $< -o $@ 

TEST_BIN =	unit_tests

TEST_SRC =	$(shell find ./src -name "*.c" -not -name "sh.c") \
	$(shell find ./tests -name "*.c")

all	:	$(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(SRC) $(PLUG) $(MEMORY_FLAG)
	make -C plugins/add_ons/

clean	:
	make -C plugins/add_ons/ clean
	rm -f $(OBJ)
	rm -f a.out
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.c~

fclean	: clean
	make -C plugins/add_ons/ fclean
	rm -f $(NAME)
	rm -f $(TEST_BIN)

re	: fclean all

$(TEST_BIN): all
	gcc -o $(TEST_BIN) $(FLAGS) $(TEST_SRC) --coverage -lcriterion

tests_run:	$(TEST_BIN)
	./$(TEST_BIN)

valgrind:
	valgrind ./$(NAME)
