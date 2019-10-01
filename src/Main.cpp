
#include <SDL2/SDL.h>
#include <stdio.h>
#include "Boilerplate.h"
#include "Fnt.h"



Uint64 lastTime = 0;

double GetDeltaTime() {
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime = (double)((now - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency());
	lastTime = now;
	return deltaTime;
}

int main(int argc, char* argv[]) {

	SDLContext context = InitSDL("Goodbye World", 800, 550);
	if (!context.success) {
		DestroySDLContext(context);
		SDL_Quit();
	}
	printf("InintSDL success");

	Sprite sprite = LoadSprite("Assets/font.bmp", &context);

	Sprite greenSprite = LoadSprite("Assets/font.bmp", &context);
	greenSprite.SetColorModulation(0, 255, 0);
	

	SDL_Event e;
	bool quit = false;
	bool leftDown = false;
	bool rightDown = false;
	int mov = 0;
	int cnt = 0;
	double frameCountDown = 0;

	double colorCountdown = 0;
	int colorMod = 0;

	//TODO(Tommy): Input handling!
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN) {
				quit = true;
				break;
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}

				if (e.key.keysym.sym == SDLK_RIGHT) { rightDown = true; }
				else if (e.key.keysym.sym == SDLK_LEFT) { leftDown = true; }
			}

			if (e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_RIGHT) { rightDown = false; }
				else if (e.key.keysym.sym == SDLK_LEFT) { leftDown = false; }
			}

		} // end of event polling

		double deltaTime = GetDeltaTime();


		// frame timer!
		frameCountDown -= deltaTime;
		if (frameCountDown <= 0) {
			frameCountDown += 100;
		}
		else {
			continue;
		}

		SDL_RenderClear(context.renderer);
		sprite.Blit(Fnt::Heart, 0, 0, &context);
		sprite.Blit(1, 8, 0, &context);
		sprite.Blit(Fnt::A, 16, 0, &context);
		greenSprite.Blit(Fnt::a, 24, 0, &context);
		sprite.Blit(Fnt::Filled, 32, 0, &context);
		sprite.Blit(Fnt::Dissolve1, 40, 0, &context);
		sprite.Blit(Fnt::Dissolve2, 48, 0, &context);
		sprite.Blit(Fnt::Dissolve3, 56, 0, &context);

		sprite.Blit(Fnt::Frame1Vert, 8*5,8*5, &context);
		sprite.Blit(Fnt::Frame1Vert, 8*7,8*5, &context);
		sprite.Blit(Fnt::Frame1Horiz, 8*6,8*4, &context);
		sprite.Blit(Fnt::Frame1Horiz, 8*6,8*6, &context);
		sprite.Blit(Fnt::Frame1TL, 8*5,8*4, &context);
		sprite.Blit(Fnt::Frame1TR, 8*5,8*6, &context);
		sprite.Blit(Fnt::Frame1BL, 8*7,8*4, &context);
		sprite.Blit(Fnt::Frame1BR, 8*7,8*6, &context);
		greenSprite.Blit(Fnt::Heart, 8*6, 8*5, &context);
		
		SDL_RenderPresent(context.renderer);
	}

	DestroySDLContext(context);
	SDL_Quit();
	return 0;
}

