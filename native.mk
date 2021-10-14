SRC_DIR := src
CC := cc
LD := ld
SRC := $(shell find -L $(SRC_DIR) -iname '*.c')
NAME := omameHTTP

default: build/.dir build/$(NAME)
	@printf "\nDone! The build output is at build/$(NAME).\n\n"

.PHONY: default

build/.dir:
	mkdir build
	touch build/.dir

build/$(NAME): 
	$(CC) $(SRC) -o $@
