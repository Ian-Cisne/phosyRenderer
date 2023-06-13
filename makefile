CFLAGS = -std=c++20 -I./src -I./include
binFolder = bin


TARGET = bin/rast
$(TARGET): src/*.cc
	g++ $(CFLAGS) -o $(TARGET) src/*.cc



.PHONY: test clean

test: bin/rast
	./bin/rast

clean:
	rm -f ./bin/rast
