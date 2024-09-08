build:
	gcc -o convex_hull -I./include/ -Wall -std=gnu17 -pedantic ./src/*.c `sdl2-config --cflags --libs`