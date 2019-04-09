#include <iostream>

#include <SDL.h>

#include "headers/simulation.h"

const int WIDTH = 640, HEIGHT = 480;
SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* argv[]){
	std::cout << "Now initializing the Game of Stuff." << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "nothing was initialized lul" << SDL_GetError() << std::endl;
	}

	window = SDL_CreateWindow("Game of Stuff", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "window could not initialize:" << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "renderer could not initialize:" << SDL_GetError() << std::endl;
	}

	Simulation coolSim(25, 25, 1);
	
	SDL_Event event;
	bool isrunning = true;
	while (isrunning) {
		while (SDL_PollEvent(&event) != 0) {
			//Caso termine o programa
			if (event.type == SDL_QUIT) {
				isrunning = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					isrunning = false;
					break;
				case SDLK_SPACE:
					coolSim.executeTurn();
					break;
				default:
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderClear(renderer);


		for (int x = 0; x < 25; x++) {
			for (int y = 0; y < 25; y++) {
				Cell& chosenOne = coolSim.board[y * 25 + x];
				if (chosenOne.living) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_Rect rect;
					rect.x = x * 8, rect.y = y * 8;
					rect.w = 8; rect.h = 8;
					SDL_RenderDrawRect(renderer, &rect);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_Rect rect;
					rect.x = x * 8, rect.y = y * 8;
					rect.w = 8; rect.h = 8;
					SDL_RenderDrawRect(renderer, &rect);
				}
			}
		}

		SDL_RenderPresent(renderer);

	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}