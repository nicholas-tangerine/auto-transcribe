CC      := gcc
CFLAGS  := -I "../include/"  -Wpedantic -Wall -Wextra -g -O2  #-Wconversion
LDFLAGS := -lm -lfftw3

SRC     := main.c input-handler.c freq-analysis.c
OBJ     := $(SRC:.c=.o)
TARGET  := main

MISC	:= *.txt

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(MISC)
