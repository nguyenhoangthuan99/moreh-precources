CXX=mpic++

CFLAGS=-std=c++14 -O3 -Wall -march=native -I/usr/local/include -g
LDFLAGS=-L/usr/local/lib
LDLIBS=-lstdc++

TARGET=memory_mountain
OBJECTS=memory_mountain.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -lm

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJECTS)

run: all
	./$(TARGET)