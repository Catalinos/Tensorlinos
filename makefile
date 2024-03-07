# Compiler settings
CC=gcc
CFLAGS=-w -fPIC
LDFLAGS=-L. -llinreg

# Target settings
TARGET_LIB=liblinreg.so
TARGET_MAIN=main
SRCS_LIB=./ml_lib/linreg.c
SRCS_MAIN=main.c

# Rule to create the shared library
create_lib:
	@echo "Creating the shared library..."
	@$(CC) $(CFLAGS) -shared -o $(TARGET_LIB) $(SRCS_LIB)

# Rule to compile the main program object file
# Note: You might need to include headers from your library here, using -I/path/to/headers
create_obj:
	@echo "Creating the object file for the main program..."
	@$(CC) $(CFLAGS) -c $(SRCS_MAIN) -o $(TARGET_MAIN).o

# Rule to compile the main program and link with the shared library
compile: create_obj
	@echo "Compiling the main program and linking with the shared library..."
	@$(CC) -o $(TARGET_MAIN) $(TARGET_MAIN).o $(LDFLAGS)

# Rule to run the main program
# Note: This temporarily sets LD_LIBRARY_PATH to ensure the shared library can be found at runtime
run:
	@echo "Running the main program..."
	@LD_LIBRARY_PATH=./:$(LD_LIBRARY_PATH) ./$(TARGET_MAIN)
	
# @export LD_LIBRARY_PATH=./:$(LD_LIBRARY_PATH)
# ./$(TARGET_MAIN)

# Rule to clean up generated files
clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET_MAIN).o $(TARGET_LIB) $(TARGET_MAIN)

# Default rule to build everything
all: create_lib compile

# Adding 'clean' as a .PHONY rule to ensure it's run as a command, not a file check
.PHONY: all create_lib create_obj compile run clean
