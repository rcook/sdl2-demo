CFLAGS := $(shell sdl2-config --cflags --libs)

main: main.cpp
	g++ -o $@ $< $(CFLAGS)
