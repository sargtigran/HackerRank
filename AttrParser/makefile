
BASE_PATH := .
INCLUDE_PATH = $(BASE_PATH)/include
SRC_PATH = $(BASE_PATH)/src
BIN_PATH = $(BASE_PATH)/bin
OBJ_PATH = $(BASE_PATH)/obj
LIB_PATH = $(BASE_PATH)/libs
TEST_PATH = $(BASE_PATH)/test

PROG := attr_parser
TARGET := $(LIB_PATH)/lib${PROG}.so
SOURCE_FILES := $(PROG).cpp
TEST_SRC := main.cpp
HEADER_FILES := $(PROG).hpp

SOURCES = $(patsubst %, $(SRC_PATH)/%, $(SOURCE_FILES))
HEADERS = $(patsubst %, $(INCLUDE_PATH)/%, $(HEADER_FILES))
TESTS   = $(patsubst %, $(TEST_PATH)/%, $(TEST_SRC))
OBJECTS = $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(SOURCE_FILES))

CC = g++ -std=c++11
DEBUG = -g
GDB = gdb
LIBS = -l$(PROG)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(LIB_PATH)
	$(CC) -shared $(DEBUG) -fPIC $(OBJ_PATH)/*.o -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $(DEBUG) -fPIC $< -I$(INCLUDE_PATH) -o $@ 
	

.PHONY: claen
clean:
	rm -rf $(OBJ_PATH) $(BIN_PATH) $(LIB_PATH)

dbg: $(BIN_PATH)/$(PROG)
	@cd $(TEST_PATH) && LD_LIBRARY_PATH=../$(LIB_PATH) $(GDB) ../$(BIN_PATH)/$(PROG)

test: $(BIN_PATH)/$(PROG)
	@cd $(TEST_PATH) && LD_LIBRARY_PATH=../$(LIB_PATH) ../$(BIN_PATH)/$(PROG)

$(BIN_PATH)/$(PROG): $(TESTS) $(TARGET) $(HEADERS)
	$(CC) $(DEBUG) -L$(LIB_PATH) -I$(INCLUDE_PATH) $< -o $@ $(LIBS)
