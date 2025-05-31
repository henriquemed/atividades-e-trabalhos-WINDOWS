CC = g++
CCFLAGS = -std=c++11 -Iinclude -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

ifeq ($(OS),Windows_NT)
    # Para Windows
    PLATFORM = windows
	TARGET = tp1.exe
	PREFIX = 
    RM_OBJS = del obj\*.o
	RM_TARGET = del $(TARGET)
else
    # Para Linux/Unix
    PLATFORM = linux
	TARGET = tp1
	PREFIX = ./
    RM_OBJS = rm -f $(OBJS)
	RM_TARGET = rm -f $(TARGET)
endif

SRCS = src/main.cpp src/graph.cpp src/capital.cpp src/utils.cpp src/battalions_and_patrols.cpp
HEADERS = include/graph.hpp include/capital.hpp include/utils.hpp include/battalions_and_patrols.hpp
OBJS = obj/main.o obj/graph.o obj/capital.o obj/utils.o obj/battalions_and_patrols.o

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

obj/capital.o: src/capital.cpp include/capital.hpp
	$(CC) $(CCFLAGS) -c src/capital.cpp -o obj/capital.o

obj/utils.o: src/utils.cpp include/utils.hpp
	$(CC) $(CCFLAGS) -c src/utils.cpp -o obj/utils.o

obj/battalions_and_patrols.o: src/battalions_and_patrols.cpp include/battalions_and_patrols.hpp
	$(CC) $(CCFLAGS) -c src/battalions_and_patrols.cpp -o obj/battalions_and_patrols.o

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