build:
	gcc -o convex_hull -Wall -std=gnu17 -pedantic ./src/*.c `sdl2-config --cflags --libs`