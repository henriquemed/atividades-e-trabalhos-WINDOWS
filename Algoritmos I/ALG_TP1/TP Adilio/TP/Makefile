# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -Iinclude -std=c++17

# Target
TARGET = tp1.exe

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

SRCS = src/main.cpp src/graph.cpp src/solutions.cpp
HEADERS = $(INC_DIR)/*.hpp
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/graph.o $(OBJ_DIR)/solutions.o

# Main target
all: $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Objects
obj/main.o: src/main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/graph.o: src/graph.cpp include/graph.hpp
	$(CXX) $(CXXFLAGS) -c src/graph.cpp -o obj/graph.o

obj/solutions.o: src/solutions.cpp include/solutions.hpp
	$(CXX) $(CXXFLAGS) -c src/solutions.cpp -o obj/solutions.o

# Run tests
test: $(TARGET)
	$(TARGET) < testCase01.txt
	$(TARGET) < testCase02.txt
	$(TARGET) < testCase03.txt
	$(TARGET) < testCase04.txt
	$(TARGET) < testCase05.txt
	$(TARGET) < testCase06.txt
	$(TARGET) < testCase07.txt
	$(TARGET) < testCase08.txt

# Clean files
clean:
	del /Q obj\*.o
	del /Q $(TARGET)
