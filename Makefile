SRC_DIR := src
TARGET := py
ELVM_DIR := ../elvm
CC := $(ELVM_DIR)/out/8cc
LIBC := $(ELVM_DIR)/libc
CFLAGS := -S -I$(LIBC) -I$(SRC_DIR) -DTARGET=ELVM_$(TARGET)
LD := $(ELVM_DIR)/out/elc
SRC := $(shell find -L $(SRC_DIR) -iname '*.c')
SRC_ASM := $(patsubst $(SRC_DIR)%,build%,$(patsubst %.c,%.eir,$(SRC)))
NAME := omameHTTP

default: build/.dir build/$(NAME).$(TARGET)
	@printf "\nDone! The build output is at build/$(NAME).$(TARGET).\n\n"

.PHONY: default

build/.dir:
	mkdir build
	touch build/.dir

build/combined.c:
	cat $(SRC) > $@

build/combined.eir: build/combined.c
	$(CC) $(CFLAGS) $< -o $@
	rm $<

build/$(NAME).$(TARGET): build/combined.eir
	$(LD) $< -$(TARGET) > $@
