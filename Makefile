build:
	g++ -std=c++17 -Wall ./src/*.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lm -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -o app

run:
	./app

clean:
	rm app
