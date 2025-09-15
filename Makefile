
CC = g++
CFLAGS = -O2 -I./headers -g3 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
LDFLAGS = -g3 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

TARGET = a.out
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
HDR_DIR = headers
OBJS = $(patsubst %.cpp, %.o, $(SRC))



$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp $(HDR_DIR)/*.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET)

.PHONY: clean