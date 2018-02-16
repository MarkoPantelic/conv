# Makefile for 'conv'

TARGET = conv
INSTALL_DIR = .

CC = gcc
CFLAGS = -Wall
LIB = -lm
DBGFLAGS = -g
OBJ = main.o marg.o nsconv.o tempconv.o weights.o chk_inval.o callconvf.o si_system.o non_si_compat.o imperial_system.o unit.o global_def.o
VPATH = marg
INCL_DIR = includes
BUILD_DIR := build



# create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))


$(BUILD_DIR)/$(TARGET): $(addprefix $(BUILD_DIR)/,$(OBJ))
	$(CC) $(LIB) -o $@ $^

$(BUILD_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -Imarg -I$(INCL_DIR) -o $@ -c $<

$(BUILD_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -I$(INCL_DIR) -o $@ -c $<
	


.PHONY: clean install uninstall

clean:
	rm -f $(addprefix $(BUILD_DIR)/,$(OBJ)) $(BUILD_DIR)/$(TARGET)

install:
	cp build/$(TARGET) $(INSTALL_DIR)
	if [ $$? -eq 0 ]; then \
		echo "'$(TARGET)' successfully installed in directory '$(INSTALL_DIR)'"; \
	else \
		echo "Install failed! Invalid permission rights ?"; \
	fi;


uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)
	if [ $$? -eq 0 ]; then \
		echo "Uninstallation successsfull, '$(INSTALL_DIR)/$(TARGET)' removed";\
	else \
		echo "Uninstall failed! Invalid permission rights ?"; \
	fi;


