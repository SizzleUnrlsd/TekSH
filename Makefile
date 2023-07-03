# Copyright (C) 2023 hugo
# 
# This file is part of TekSH.
# 
# TekSH is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# TekSH is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with TekSH.  If not, see <http://www.gnu.org/licenses/>.

SRC	=	$(shell find ./src -name "*.c")

PLUG =	plugins/add_ons/loader.c

CC	=	gcc

OBJ	=	$(SRC:.c=.o) $(PLUG:.c=.o)

NAME	=	teksh

CFLAGS 	=	@flag_makefile/cflags.txt

LDLIBS = @flag_makefile/ldlibs.txt

MEMORY_FLAG	=	@flag_makefile/memory_flags.txt

NODEADCODE	=	@flag_makefile/nodeadcode.txt

UNAME_S := $(shell uname -s)

TEST_BIN =	unit_tests

TEST_SRC =	$(shell find ./src -name "*.c" -not -name "sh.c") \
	$(shell find ./tests -name "*.c")

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

all	:	$(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(SRC) $(PLUG) $(LDLIBS)
	make -C plugins/add_ons/

debug: CFLAGS += -DDEBUG -g3

debug: $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(SRC) $(PLUG) $(LDLIBS)
	make -C plugins/add_ons/

clean	:
	make -C plugins/add_ons/ clean
	rm -f $(OBJ)
	rm -f a.out
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.c~
	rm -f $(OBJ:.o=.i)
	rm -f $(OBJ:.o=.s)

fclean	: clean
	make -C plugins/add_ons/ fclean
	rm -f $(NAME)
	rm -f $(TEST_BIN)

re	: fclean all

$(TEST_BIN): all
	gcc -o $(TEST_BIN) $(FLAGS) $(TEST_SRC) --coverage -lcriterion

tests_run:	$(TEST_BIN)
	./$(TEST_BIN)

tests_build:
	cd tests && ./test_build.sh