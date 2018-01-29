# Makefile for 'conv'

TARGET = conv

CC = gcc
CFLAGS = -Wall
LIB = -lm
DBGFLAGS = -g
OBJ = main.o marg.o nsconv.o tempconv.o chk_inval.o callconvf.o
BUILD_DIR = build
VPATH = marg
INCL_DIR = includes

$(TARGET): $(addprefix $(BUILD_DIR)/,$(OBJ))
	$(CC) $(LIB) -o $@ $^

$(BUILD_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -Imarg -I$(INCL_DIR) -o $@ -c $<

$(BUILD_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -I$(INCL_DIR) -o $@ -c $<

	
.PHONY: clean
clean:
	rm -f $(addprefix $(BUILD_DIR)/,$(OBJ)) $(TARGET)


#TODO
#install:
#	cp build/$(TARGET) $(BIN_DIR)
#
#unnstall:
#	rm build/$(TARGET) $(BIN_DIR)
#


