CC          = clang
CFLAGS      = -I include -std=c11

OBJ         = src/error.o src/interpret.o src/io.o src/main.o src/stack.o

DEBUG ?= 0
ifeq ($(DEBUG), 0)
    CFLAGS += -O2
else
    CFLAGS += -O0
endif

# to disable auto cleanup, comment out the following rule, or run `make bf`
all: bf clean

bf: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@

clean:
	$(RM) src/*.o

.PHONY: clean
