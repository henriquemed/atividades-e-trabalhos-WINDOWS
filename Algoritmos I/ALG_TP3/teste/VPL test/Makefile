CC = g++
CCFLAGS = -std=c++11 -Iinclude -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

ifeq ($(OS),Windows_NT)
    # Para Windows
    PLATFORM = windows
	TARGET = tp3.exe
	PREFIX = 
    RM_OBJS = del obj\*.o
	RM_TARGET = del $(TARGET)
else
    # Para Linux/Unix
    PLATFORM = linux
	TARGET = tp3
	PREFIX = ./
    RM_OBJS = rm -f $(OBJS)
	RM_TARGET = rm -f $(TARGET)
endif

SRCS = src/main.cpp src/graph.cpp src/brute.cpp src/dynamic.cpp src/greedy.cpp
HEADERS = include/graph.hpp include/brute.hpp include/dynamic.hpp include/greedy.hpp
OBJS = obj/main.o obj/graph.o obj/brute.o obj/dynamic.o obj/greedy.o

# alvo principal
all: $(TARGET)

# rodar o programa
run: $(TARGET)
	./$(TARGET)

# executável
$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJS)

# objetos
obj/main.o: src/main.cpp $(HEADERS)
	$(CC) $(CCFLAGS) -c src/main.cpp -o obj/main.o

obj/graph.o: src/graph.cpp include/graph.hpp
	$(CC) $(CCFLAGS) -c src/graph.cpp -o obj/graph.o

obj/brute.o: src/brute.cpp include/brute.hpp
	$(CC) $(CCFLAGS) -c src/brute.cpp -o obj/brute.o

obj/dynamic.o: src/dynamic.cpp include/dynamic.hpp
	$(CC) $(CCFLAGS) -c src/dynamic.cpp -o obj/dynamic.o

obj/greedy.o: src/greedy.cpp include/greedy.hpp
	$(CC) $(CCFLAGS) -c src/greedy.cpp -o obj/greedy.o

# testes
test: $(TARGET)
	$(PREFIX)$(TARGET) < testCase01.txt
	$(PREFIX)$(TARGET) < testCase02.txt
	$(PREFIX)$(TARGET) < testCase03.txt
	$(PREFIX)$(TARGET) < testCase04.txt
	$(PREFIX)$(TARGET) < testCase05.txt
	$(PREFIX)$(TARGET) < testCase06.txt
	$(PREFIX)$(TARGET) < testCase07.txt
	$(PREFIX)$(TARGET) < testCase08.txt

# limpar arquivos
clean:
	$(RM_OBJS)
	$(RM_TARGET)