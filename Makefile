CC      	:= gcc
CFLAGS  	:= -I "include/"  -Wpedantic -Wall -Wextra -g -O2  #-Wconversion
LDFLAGS 	:= -lm -lfftw3

SRC_DIR 	:= src
BUILD_DIR 	:= build

SRC     	:= main.c \
			   	   miniaudio.c \
				   input-handler.c \
				   freq-analysis.c \
				   music-analysis.c
OBJ 		:= $(SRC:%.c=$(BUILD_DIR)/%.o)
TARGET  	:= main

MISC		:= *.txt

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(MISC)
